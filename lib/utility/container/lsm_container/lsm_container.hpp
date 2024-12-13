#ifndef _LSM_CONTAINER_HPP_
#define _LSM_CONTAINER_HPP_

#include <concepts>
#include <iosfwd>
#include <system_error>
#include <type_traits>
#include <utility>
#include <string>
#include <string_view>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <deque>
#include <fstream>
#include <forward_list>

#include <time_device/unique_name_generator/unique_name_generator.hpp>

namespace battleship {

namespace {

template<typename Type, typename = void>
struct has_key_compare : std::false_type {
  using Compare = void;
};
template<typename Type>
struct has_key_compare<Type, std::void_t<typename Type::key_compare>> : std::true_type {
  using Compare = typename Type::key_compare;
};

template<typename Type, typename = void>
struct has_key_equal : std::false_type {
  using Compare = void;
};
template<typename Type>
struct has_key_equal<Type, std::void_t<typename Type::key_equal>> : std::true_type {
  using Compare = typename Type::key_equal;
};

template<typename ContType>
concept IsContainer = requires (ContType cont) {
  std::disjunction_v<
    has_key_compare<ContType>,
    has_key_equal<ContType>
  > == true;

  typename ContType::mapped_type;
  typename ContType::value_type;
  typename ContType::size_type;
  typename ContType::difference_type;
  typename ContType::reference ;
  typename ContType::const_reference;
  typename ContType::pointer;
  typename ContType::const_pointer;
  typename ContType::iterator;
  typename ContType::const_iterator;
  {cont.size()} -> std::same_as<typename ContType::size_type>;
};

template<typename Type1, typename Type2>
concept CanCompare = requires(Type1 val1, Type2 val2) {
  {val1 == val2} -> std::same_as<bool>;
  {val1 != val2} -> std::same_as<bool>;
  {val1 >= val2} -> std::same_as<bool>;
  {val1 <= val2} -> std::same_as<bool>;
  {val1 > val2} -> std::same_as<bool>;
  {val1 < val2} -> std::same_as<bool>;

  {val2 == val1} -> std::same_as<bool>;
  {val2 != val1} -> std::same_as<bool>;
  {val2 >= val1} -> std::same_as<bool>;
  {val2 <= val1} -> std::same_as<bool>;
  {val2 > val1} -> std::same_as<bool>;
  {val2 < val1} -> std::same_as<bool>;
};

template<typename Type>
consteval bool IsTrivialDump() {
  return (std::is_aggregate_v<Type> ||
    std::is_fundamental_v<Type>) &&
    !std::is_pointer_v<Type>;
}

} // namespace

template<std::size_t kMaxCount, IsContainer ContType>
class LsmContainer {
 private:
  static constexpr std::string_view error_description_ = "lsm error message:\n";
 private:
  using key_type = ContType::key_type;
  using key_compare = 
    std::conditional_t<has_key_compare<ContType>::value,
      typename has_key_compare<ContType>::Compare,
      typename has_key_equal<ContType>::Compare
    >;
  using data_type = ContType::mapped_type;
  using value_type = ContType::value_type;
  using size_type = ContType::size_type;
  using difference_type = ContType::difference_type;
  using reference = ContType::reference ;
  using const_reference = ContType::const_reference;
  using pointer = ContType::pointer;
  using const_pointer = ContType::const_pointer;
  using iterator = ContType::iterator;
  using const_iterator = ContType::const_iterator;

  using file_count_type = std::size_t;
 public:
  LsmContainer(std::string path, ContType&& cont);

  LsmContainer(const LsmContainer& value);

  LsmContainer(LsmContainer&& value);

  LsmContainer& operator=(const LsmContainer& value);

  LsmContainer& operator=(LsmContainer&& value);

  ~LsmContainer();

 public:
  std::pair<iterator, bool> Add(const value_type& data);
  std::pair<iterator, bool> Add(value_type&& data);
  void AddCont(ContType&& data);

 public:
  template<std::equality_comparable_with<key_type> KeyT>
  std::pair<LsmContainer<kMaxCount, ContType>::data_type, bool>
    Find(const KeyT& key) const;

 public:
  template<std::equality_comparable_with<key_type> KeyT>
  bool Remove(const KeyT& key);

  template<std::equality_comparable_with<key_type> KeyT, std::invocable<data_type&> FuncType>
  bool Modify(const KeyT& key, const FuncType& func);

  template<std::equality_comparable_with<key_type> KeyT>
  ContType Load(const KeyT& key);
  void Dump();

  ContType Upload();

 public:
  std::forward_list<size_type> Size() const;
  bool IsValid() { return state_; };
  void Clear();

 private:
  template<std::equality_comparable_with<key_type> KeyT>
  std::pair<data_type, bool>
    Find(const std::filesystem::path& file_path, const KeyT& key) const;

  template<std::equality_comparable_with<key_type> KeyT, std::invocable<data_type&> FuncType>
  bool Modify(const std::filesystem::path& file_path, const KeyT& key, const FuncType& func);


  template<std::equality_comparable_with<key_type> KeyT>
  bool Remove(const std::filesystem::path& file_path, const KeyT& key);
  ContType Load(const std::filesystem::path& file_path);

  void Dump(ContType& cont);

  std::pair<value_type, bool> ParseData(std::fstream& file, std::streampos beg_pos) const;
  bool DumpData(const value_type& data, std::fstream& file, std::streampos beg_pos) const;

 private:
  std::tuple<std::streampos, std::streampos, size_type>
    GetMetadata(const std::filesystem::path& path) const;

  static constexpr uint64_t kMetadataOffset = 
    -(sizeof(std::streampos) * 2 + sizeof('\t') * 2 + sizeof(size_type));

 private:

 private:
  bool state_ = false;
  ContType cont_;
  std::filesystem::path path_;
  std::string original_path_;
};

#include "lsm_container.inc"

template<std::size_t kMaxCount, IsContainer ContType>
LsmContainer<kMaxCount, ContType>::LsmContainer(std::string path, ContType&& cont)
  : path_("./" + path + "_" + UniqueNameGenerator::GetString()), cont_(cont), original_path_(path) {
  try {
    state_ = std::filesystem::create_directories(path_);
  } catch (std::filesystem::filesystem_error& ex) {
    std::cerr << LsmContainer<kMaxCount, ContType>::error_description_;
    std::cout << path_ << std::endl;
    std::cerr << ex.what() << std::endl;
    state_ = false;
  } catch (std::error_code& ex) {
    std::cerr << LsmContainer<kMaxCount, ContType>::error_description_;
    std::cout << path_ << std::endl;
    std::cerr << "error code: "<< ex.value() << std::endl;
    state_ = false;
  } catch (...) {
    std::cerr << LsmContainer<kMaxCount, ContType>::error_description_;
    std::cout << path_ << std::endl;
    state_ = false;
  }
};

template<std::size_t kMaxCount, IsContainer ContType>
LsmContainer<kMaxCount, ContType>::LsmContainer(const LsmContainer& value) :
  path_(value.original_path_ + "_" + UniqueNameGenerator::GetString() + "_" + "copy"),
    cont_(value.cont_), original_path_(value.original_path_) { 
  try {
    state_ = std::filesystem::create_directories(path_);
    std::filesystem::copy(value.path_,
      path_, std::filesystem::copy_options::overwrite_existing);
  } catch (std::filesystem::filesystem_error& ex) {
    std::cerr << LsmContainer<kMaxCount, ContType>::error_description_;
    std::cout << path_ << std::endl;
    std::cerr << ex.what() << std::endl;
    state_ = false;
  } catch (std::error_code& ex) {
    std::cerr << LsmContainer<kMaxCount, ContType>::error_description_;
    std::cout << path_ << std::endl;
    std::cerr << "error code: "<< ex.value() << std::endl;
    state_ = false;
  } catch (...) {
    std::cerr << LsmContainer<kMaxCount, ContType>::error_description_;
    std::cout << path_ << std::endl;
    state_ = false;
  }
};

template<std::size_t kMaxCount, IsContainer ContType>
LsmContainer<kMaxCount, ContType>::LsmContainer(LsmContainer&& value) :
  path_(std::move(value.path_)), original_path_(std::move(value.original_path_)),
    cont_(std::move(value.cont_)), state_(value.state_) { value.state_ = false; };

template<std::size_t kMaxCount, IsContainer ContType>
LsmContainer<kMaxCount, ContType>& 
  LsmContainer<kMaxCount, ContType>::operator=(const LsmContainer& value) {
  if (this == &value)
    return *this;

  if (state_)
    std::filesystem::remove_all(path_);

  path_ = value.original_path_ + "_" + UniqueNameGenerator::GetString();
  cont_ = value.cont_;
  original_path_ = value.original_path_;

  try {
    state_ = std::filesystem::create_directories(path_);
    std::filesystem::copy(value.path_,
      path_, std::filesystem::copy_options::overwrite_existing);
  } catch (std::filesystem::filesystem_error& ex) {
    std::cerr << LsmContainer<kMaxCount, ContType>::error_description_;
    std::cout << path_ << std::endl;
    std::cerr << ex.what() << std::endl;
    state_ = false;
  } catch (std::error_code& ex) {
    std::cerr << LsmContainer<kMaxCount, ContType>::error_description_;
    std::cout << path_ << std::endl;
    std::cerr << "error code: "<< ex.value() << std::endl;
    state_ = false;
  } catch (...) {
    std::cerr << LsmContainer<kMaxCount, ContType>::error_description_;
    std::cout << path_ << std::endl;
    state_ = false;
  }

  return *this;
};

template<std::size_t kMaxCount, IsContainer ContType>
LsmContainer<kMaxCount, ContType>&
  LsmContainer<kMaxCount, ContType>::operator=(LsmContainer&& value) {
  if (this == &value)
    return *this;

  if (state_)
    std::filesystem::remove_all(path_);

  path_ = std::move(value.path_);
  original_path_ = std::move(value.original_path_);
  cont_ = std::move(value.cont_);
  state_ = value.state_;
  value.state_ = false;
  return *this;
};

#define CORRECT_DTOR
#ifdef CORRECT_DTOR
template<std::size_t kMaxCount, IsContainer ContType>
LsmContainer<kMaxCount, ContType>::~LsmContainer() {
  if (!state_) {
    return;
  }

  Clear();

  try {
    std::filesystem::remove_all(path_);
  } catch (std::filesystem::filesystem_error& ex) {
    std::cerr << LsmContainer<kMaxCount, ContType>::error_description_;
    std::cout << path_ << std::endl;
    std::cerr << ex.what() << std::endl;
  } catch (std::error_code& ex) {
    std::cerr << LsmContainer<kMaxCount, ContType>::error_description_;
    std::cout << path_ << std::endl;
    std::cerr << "error code: "<< ex.value() << std::endl;
  } catch (...) {
    std::cerr << LsmContainer<kMaxCount, ContType>::error_description_;
    std::cout << path_ << std::endl;
  }
};
#else
template<std::size_t kMaxCount, IsContainer ContType>
LsmContainer<kMaxCount, ContType>::~LsmContainer() {  };
#endif // CORRECT_DTOR

template<std::size_t kMaxCount, IsContainer ContType>
std::pair<typename LsmContainer<kMaxCount, ContType>::iterator, bool>
  LsmContainer<kMaxCount, ContType>::Add(const value_type& data) {
  if (kMaxCount - 1 < cont_.size()) {
    try {
      Dump();
    } catch (std::runtime_error& ex){
      std::cerr << LsmContainer::error_description_;
      std::cerr << ex.what();
      return {cont_.end(), false};
    } catch(...) {
      std::cerr << LsmContainer::error_description_;
      std::cerr << "dump fail: cannot open file( \n";
      return {cont_.end(), false};
    }
  }

  return cont_.insert(data);

};

template<std::size_t kMaxCount, IsContainer ContType>
std::pair<typename LsmContainer<kMaxCount, ContType>::iterator, bool>
  LsmContainer<kMaxCount, ContType>::Add(value_type&& data) {
  if (kMaxCount - 1 < cont_.size()) {
    try {
      Dump();
    } catch (std::runtime_error& ex){
      std::cerr << LsmContainer::error_description_;
      std::cerr << ex.what();
      return {cont_.end(), false};
    } catch(...) {
      std::cerr << LsmContainer::error_description_;
      std::cerr << "dump fail: cannot open file( \n";
      return {cont_.end(), false};
    }
  }

  return cont_.insert(data);
};

template<std::size_t kMaxCount, IsContainer ContType>
std::pair<typename LsmContainer<kMaxCount, ContType>::value_type, bool>
  LsmContainer<kMaxCount, ContType>::ParseData(std::fstream& file,
    std::streampos beg_pos) const {
  key_type key;
  data_type data;

  file.seekg(beg_pos);
  char ch_buff[2];
  file.read(ch_buff, 2);
  if (ch_buff[0] == '\0' && ch_buff[1] == '\0') {
    std::string buff_line;
    std::getline(file, buff_line);
    return {{}, false};
  }

  file.seekg(beg_pos);
  if constexpr(IsTrivialDump<key_type>()) {
    file.read(reinterpret_cast<char*>(&key), sizeof(key));
  } else {
    file >> key;
  }

  // tab skip
  file.get();

  if constexpr(IsTrivialDump<data_type>()) {
    file.read(reinterpret_cast<char*>(&data), sizeof(data));
  } else {
    file >> data;
  }

  // terminator skip
  file.get();

  return {{key, data}, true};
};

template<std::size_t kMaxCount, IsContainer ContType>
void LsmContainer<kMaxCount, ContType>::AddCont(ContType&& data) {
  if (!cont_.size()) {
    cont_ = std::move(data);
    return;
  }

  Dump(data);
  data.clear();
};

template<std::size_t kMaxCount, IsContainer ContType>
template<std::equality_comparable_with<typename LsmContainer<kMaxCount, ContType>::key_type> KeyT>
std::pair<typename LsmContainer<kMaxCount, ContType>::data_type, bool>
  LsmContainer<kMaxCount, ContType>::Find(const std::filesystem::path& file_path, const KeyT& key) const {
  std::fstream file;

  file.open(file_path, std::ios::in | std::ios::ate | std::ios::binary);
  if (!file.is_open()) {
    std::cerr << LsmContainer::error_description_;
    throw std::runtime_error("cannot open file to read:" + file_path.string());
  }

  // parse metadata
  auto [data_begin, data_end, elem_count] = GetMetadata(file_path);

  file.seekg(data_begin);

  auto min_data = ParseData(file, data_begin).first;
  if (min_data.first == key)
    return {min_data.second, true};

  auto max_data = ParseData(file, data_end).first;
  if (max_data.first == key)
    return {max_data.second, true};

  if (key < min_data.first || max_data.first < key)
    return {data_type{}, false};

#if 0
  // bin-search value
  auto left_pos = data_begin;
  auto right_pos = data_end;

  std::string line_buff;

  while (right_pos > left_pos) {
    decltype(left_pos) mid_pos = left_pos + ((static_cast<std::streamoff>(right_pos - left_pos) / 2) + 1);
    // partial line skip
    file.seekg(mid_pos);
    char ch;
    file.get(ch);
    if (ch != '\n') {
      std::getline(file, line_buff);
      mid_pos = file.tellg();
    }
#if 0
    std::cout << "midpos diff: " << mid_pos - file.tellg() << std::endl;
#endif

    auto data_buff = ParseData(file, mid_pos);

    if (data_buff.first > key) {
      right_pos = mid_pos;
    } else if (data_buff.first < key) {
      // mid_pos = file.tellg();
      left_pos = mid_pos;
    } else {
      return {data_buff.second, true};
    }
  }
#if 0
  std::cout << file_path << std::endl;
#endif
  return {data_type{}, false};
#endif
  // O(n) search
  file.seekg(data_begin);
  while (file.tellg() != data_end) {
    if (auto value = ParseData(file, file.tellg());
      value.second && value.first.first == key) {
      return {value.first.second, true};
    }
  }
  return {data_type{}, false};
};

template<std::size_t kMaxCount, IsContainer ContType>
template<std::equality_comparable_with<typename LsmContainer<kMaxCount, ContType>::key_type> KeyT>
std::pair<typename LsmContainer<kMaxCount, ContType>::data_type, bool>
  LsmContainer<kMaxCount, ContType>::Find(const KeyT& key) const {
  if (auto find_itr = cont_.find(key); find_itr != cont_.end()) {
    return {find_itr->second, true};
  }

  for (auto&& itr : std::filesystem::directory_iterator{path_}) {
    if (auto search_res = Find(itr.path(), key);
      search_res.second) {
      return search_res;
    }
  }

  return {data_type{}, false};
};

template<std::size_t kMaxCount, IsContainer ContType>
template<std::equality_comparable_with<typename LsmContainer<kMaxCount, ContType>::key_type> KeyT>
bool LsmContainer<kMaxCount, ContType>::Remove(const std::filesystem::path& file_path,
  const KeyT& key) {
  std::fstream file;

  file.open(file_path, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
  if (!file.is_open()) {
    std::cerr << LsmContainer::error_description_;
    throw std::runtime_error("cannot open file to read:" + file_path.string());
  }

  // parse metadata
  auto [data_begin, data_end, elem_count] = GetMetadata(file_path);

  std::streampos prev_pos = -1;

  file.seekg(data_begin);
  auto value = std::pair{std::pair<key_type, data_type>{}, false};

  auto min_data = ParseData(file, data_begin);
  if (min_data.first.first == key) {
    prev_pos = data_begin;
    value = std::pair{min_data.first, true};
  }

  auto max_data = ParseData(file, data_end);
  if (max_data.first.first  == key) {
    prev_pos = data_end;
    value = std::pair{max_data.first, true};
  }

  if (key < min_data.first.first || max_data.first.first < key) {
    return false;
  }

  // O(n) search
  file.seekg(data_begin);

  if (prev_pos == data_end) {
    while (file.tellg() != prev_pos) {
      auto current_pos = file.tellg();
      if (auto tmp_data = ParseData(file, current_pos);
        tmp_data.second && current_pos != prev_pos) {
        data_end = current_pos;
      }
    }
  } else if (prev_pos != data_begin) {
    while (file.tellg() != data_end) {
      prev_pos = file.tellg();
      if (value = ParseData(file, prev_pos);
        value.second && value.first.first == key) {
        break;
      }
    }
  }

  if (value.first.first == key) {
    file.seekp(prev_pos);
    file.put('\0');
    file.put('\0');
    --elem_count;
  }

  // update data begin
  if (prev_pos == data_begin && elem_count != 0) {
    file.seekg(prev_pos);
    std::string buff_line;
    std::getline(file, buff_line);
    data_begin = file.tellg();
    while (file.tellg() != data_end) {
      if (auto data = ParseData(file, file.tellg());
        data.second) {
          break;
      }
      data_begin = file.tellg();
    }
  }

  // update metadata
  file.seekg(kMetadataOffset, std::ios::end);
  file.write(reinterpret_cast<char*>(&data_begin), sizeof(data_begin));
  file.put('\t');
  file.write(reinterpret_cast<char*>(&data_end), sizeof(data_end));
  file.put('\t');
  file.write(reinterpret_cast<char*>(&elem_count), sizeof(elem_count));
  file.close();

  if (!elem_count) {
    std::filesystem::remove(file_path);
  }

  return value.first.first == key;
};

template<std::size_t kMaxCount, IsContainer ContType>
template<std::equality_comparable_with<typename LsmContainer<kMaxCount, ContType>::key_type> KeyT>
bool LsmContainer<kMaxCount, ContType>::Remove(const KeyT& key) {
  if (cont_.erase(key) > 0) {
    return true;
  }

  for (auto&& itr : std::filesystem::directory_iterator{path_}) {
    if (auto search_res = Remove(itr.path(), key); search_res) {
      return search_res;
    }
  }

  return false;
};

template<std::size_t kMaxCount, IsContainer ContType>
void LsmContainer<kMaxCount, ContType>::Dump() {
  Dump(cont_);
};

template<std::size_t kMaxCount, IsContainer ContType>
void LsmContainer<kMaxCount, ContType>::Dump(ContType& cont) {
  std::filesystem::path file_path =
    path_ / ("dump_" + UniqueNameGenerator::GetString() + "_" + 
      std::to_string(std::distance(std::filesystem::directory_iterator(path_),
                     std::filesystem::directory_iterator{})) +
        ".lsm_dump");

  std::fstream file;
  file.open(file_path, std::ios::out | std::ios::beg | std::ios::binary);

  if (!file.is_open()) {
    std::cerr << LsmContainer::error_description_;
    throw std::runtime_error("cannot open file to dump:" + file_path.string());
  }


  // dump process:
  std::streampos data_begin = 0;
  std::streampos data_end = 0;
  size_type last_elem_ind = 0;

  if constexpr(has_key_compare<ContType>::value) {
    for (auto&& elem : cont) {
      if (last_elem_ind == 0) {
        data_begin = file.tellp();
      }
      if (last_elem_ind + 1 == cont.size()) {
        data_end = file.tellp();
      }

      if constexpr(IsTrivialDump<key_type>()) {
        file.write(reinterpret_cast<const char*>(&(elem.first)), sizeof(elem.first));
      } else {
        file << elem.first;
      }

      file << '\t';

      if constexpr(IsTrivialDump<data_type>()) {
        file.write(reinterpret_cast<const char*>(&(elem.second)), sizeof(elem.second));
      } else {
        file << elem.second;
      }

      file << '\n';

      ++last_elem_ind;
    }
  } else {
    // sort container

    std::deque<key_type> ordered_cont;
    std::for_each(cont.begin(), cont.end(), [&ordered_cont](const value_type& elem){
      ordered_cont.push_front(elem.first);
    });

    std::sort(ordered_cont.begin(), ordered_cont.end(),
      [](const key_type& lhs_elem, const key_type& rhs_elem) {
          return lhs_elem < rhs_elem;
      });

    for (auto&& elem : ordered_cont) {
      if (last_elem_ind == 0) {
        data_begin = file.tellp();
      }
      if (last_elem_ind + 1 == cont.size()) {
        data_end = file.tellp();
      }

      if constexpr(IsTrivialDump<key_type>()) {
        file.write(reinterpret_cast<const char*>(&(elem)), sizeof(elem));
      } else {
        file << elem;
      }

      file << '\t';

      if constexpr(IsTrivialDump<data_type>()) {
        file.write(reinterpret_cast<const char*>(&(cont[elem])), sizeof(cont[elem]));
      } else {
        file << cont[elem];
      }

      file << '\n';

      ++last_elem_ind;
    }
  }

  // metadata out
  file.write(reinterpret_cast<const char*>(&data_begin), sizeof(data_begin));
  file << '\t';
  file.write(reinterpret_cast<const char*>(&data_end), sizeof(data_end));
  file << '\t';
  auto cont_size = cont_.size();
  file.write(reinterpret_cast<const char*>(&cont_size), sizeof(cont_size));

  cont.clear();
};

template<std::size_t kMaxCount, IsContainer ContType>
std::forward_list<typename LsmContainer<kMaxCount, ContType>::size_type> 
  LsmContainer<kMaxCount, ContType>::Size() const {
  std::forward_list<size_type> size_cont = { cont_.size() };

  std::for_each(std::filesystem::directory_iterator(path_),
    std::filesystem::directory_iterator(),
    [this, &size_cont](const std::filesystem::path& file_path){
      auto [beg, end, size] = GetMetadata(file_path);
      size_cont.push_front(size);
    });
  return size_cont;
};

template<std::size_t kMaxCount, IsContainer ContType>
void LsmContainer<kMaxCount, ContType>::Clear() {
  if (state_) {
    try {
      for (auto&& subpath
        : std::filesystem::directory_iterator{path_}) {
        std::filesystem::remove_all(subpath);
      }
    } catch (std::filesystem::filesystem_error& ex) {
      std::cerr << LsmContainer<kMaxCount, ContType>::error_description_;
      std::cout << path_ << std::endl;
      std::wcerr << ex.what() << std::endl;
    } catch (std::error_code& ex) {
      std::cerr << LsmContainer<kMaxCount, ContType>::error_description_;
      std::cout << path_ << std::endl;
      std::cerr << "error code: "<< ex.value() << std::endl;
    } catch (...) {
      std::cerr << LsmContainer<kMaxCount, ContType>::error_description_;
      std::cout << path_ << std::endl;
    }
  }
  cont_.clear();
};

template<std::size_t kMaxCount, IsContainer ContType>
std::tuple<std::streampos, std::streampos, typename LsmContainer<kMaxCount, ContType>::size_type>
  LsmContainer<kMaxCount, ContType>::GetMetadata(const std::filesystem::path& path) const {
  std::fstream file;

  file.open(path, std::ios::in | std::ios::ate | std::ios::binary);
  if (!file.is_open()) {
    std::cerr << LsmContainer::error_description_;
    throw std::runtime_error("cannot open file to read:" + path.string());
  }

  // parse metadata
  file.seekg(kMetadataOffset, std::ios::end);

  std::streampos data_begin;
  std::streampos data_end;
  size_type elem_count;

  file.read(reinterpret_cast<char*>(&data_begin), sizeof(data_begin));
  file.get();
  file.read(reinterpret_cast<char*>(&data_end), sizeof(data_end));
  file.get();
  file.read(reinterpret_cast<char*>(&elem_count), sizeof(elem_count));

  return {data_begin, data_end, elem_count};
};

template<std::size_t kMaxCount, IsContainer ContType>
template<std::equality_comparable_with<typename LsmContainer<kMaxCount, ContType>::key_type> KeyT>
ContType LsmContainer<kMaxCount, ContType>::Load(const KeyT& key) {
  ContType load_cont;
  if (auto find_itr = cont_.find(key); find_itr != cont_.end()) {
    load_cont = std::move(cont_);
    cont_.clear();
    return load_cont;
  }

  for (auto&& itr : std::filesystem::directory_iterator{path_}) {
    if (auto search_res = Find(itr.path(), key);
      search_res.second) {
      load_cont = Load(itr.path());
      std::filesystem::remove(itr.path());
      return load_cont;
    }
  }

  return {};
};

template<std::size_t kMaxCount, IsContainer ContType>
ContType LsmContainer<kMaxCount, ContType>::Load(const std::filesystem::path& file_path) {
  ContType cont;
  std::fstream file;
  file.open(file_path, std::ios::in | std::ios::ate | std::ios::binary);
  if (!file.is_open()) {
    std::cerr << LsmContainer::error_description_;
    throw std::runtime_error("cannot open file to read:" + file_path.string());
  }

  // parse metadata
  auto [data_begin, data_end, elem_count] = GetMetadata(file_path);

  file.seekg(data_begin);
  while (file.tellg() != data_end) {
    if (auto value = ParseData(file, file.tellg());
      value.second) {
      cont.insert({value.first.first, value.first.second});
    }
  }

  return cont;
};

template<std::size_t kMaxCount, IsContainer ContType>
ContType LsmContainer<kMaxCount, ContType>::Upload() {
  ContType old_cont = std::move(cont_);
  cont_.clear();

  if (std::filesystem::directory_iterator{path_} != std::filesystem::directory_iterator{})
    cont_ = Load(std::filesystem::directory_iterator{path_}->path());
  return old_cont;
};

template<std::size_t kMaxCount, IsContainer ContType>
bool LsmContainer<kMaxCount, ContType>::DumpData(
  const LsmContainer<kMaxCount, ContType>::value_type& data, std::fstream& file,
  std::streampos beg_pos) const {

  file.seekg(beg_pos);
  if constexpr(IsTrivialDump<key_type>()) {
    file.write(reinterpret_cast<const char*>(&data.first), sizeof(data.first));
  } else {
    file << data.first;
  }

  // tab separator
  file.put('\t');

  if constexpr(IsTrivialDump<data_type>()) {
    file.write(reinterpret_cast<const char*>(&data.second), sizeof(data.second));
  } else {
    file << data.second;
  }

  // terminator
  file.put('\n');

  return true;
};

template<std::size_t kMaxCount, IsContainer ContType>
template<std::equality_comparable_with<typename LsmContainer<kMaxCount, ContType>::key_type> KeyT,
  std::invocable<typename LsmContainer<kMaxCount, ContType>::data_type&> FuncType>
bool LsmContainer<kMaxCount, ContType>::Modify(const KeyT& key, const FuncType& func) {
  if (auto find_itr = cont_.find(key); find_itr != cont_.end()) {
    func(find_itr->second);
    return true;
  }

  if (std::filesystem::directory_iterator{path_} 
    != std::filesystem::directory_iterator{}) {
    return false;
  }

  for (auto&& itr : std::filesystem::directory_iterator{path_}) {
    if (Modify(itr.path(), key, func)) {
      return true;
    }
  }

  return false;
};

template<std::size_t kMaxCount, IsContainer ContType>
template<std::equality_comparable_with<typename LsmContainer<kMaxCount, ContType>::key_type> KeyT,
  std::invocable<typename LsmContainer<kMaxCount, ContType>::data_type&> FuncType>
bool LsmContainer<kMaxCount, ContType>::Modify(const std::filesystem::path& file_path,
  const KeyT& key, const FuncType& func) {
  std::fstream file;

  file.open(file_path, std::ios::in | std::ios::ate | std::ios::binary);
  if (!file.is_open()) {
    std::cerr << LsmContainer::error_description_;
    throw std::runtime_error("cannot open file to read:" + file_path.string());
  }

  // parse metadata
  auto [data_begin, data_end, elem_count] = GetMetadata(file_path);

  file.seekg(data_begin);

  auto min_data = ParseData(file, data_begin).first;
  if (min_data.first == key) {
    func(min_data.second);
    DumpData(min_data, file, data_begin);
    return true;
  }

  auto max_data = ParseData(file, data_end).first;
  if (max_data.first == key) {
    func(max_data.second);
    DumpData(max_data, file, data_begin);
    return true;
  }

  if (key < min_data.first || max_data.first < key) {
    return false;
  }

  // O(n) search
  file.seekg(data_begin);
  while (file.tellg() != data_end) {
    std::streampos view_pos = file.tellg();
    if (auto value = ParseData(file, view_pos);
      value.second && value.first.first == key) {
      func(value.first.second);
      DumpData(value.first, file, view_pos);
      return true;
    }
  }

  return false;
};

} // battleship

#endif // _LSM_CONTAINER_HPP_