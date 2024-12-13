#include <cstdint>
#include <iostream>
#include <new>
#include <string>
#include <unordered_map>
#include <map>

#include <time_device/unique_name_generator/unique_name_generator.hpp>
#include "lsm_container.hpp"

// #define CREATION_TEST
// #define ADD_TEST
// #define FIND_TEST
// #define REMOVE_TEST
// #define VECTOR_MURDERING
// #define SIZE_TEST

#ifdef ADD_TEST
#include <ostream>
struct test_data_t {
  uint64_t a, b;
};

std::ostream& operator<<(std::ostream& stream, const test_data_t& val) {
  return stream << val.a << val.b;
};

#endif

#ifdef FIND_TEST
  struct key {
    key() : data_(0) {  };
    key(int64_t data) : data_(data) {  };
    int64_t data_;
    bool operator<(const key& rhs) {
      return data_ < rhs.data_;
    }
    bool operator>(const key& rhs) {
      return data_ < rhs.data_;
    }
    bool operator==(const key& rhs) {
      return data_ == rhs.data_;
    }
  };

  std::ostream& operator<<(std::ostream& stream, const key& k) {
    return stream << k.data_;
  };
  std::istream& operator>>(std::istream& stream, const key& k) {
    return stream >> k.data_;
  };
#endif // FIND_TEST

int main(int, char**) {
  using namespace battleship;
#ifdef CREATION_TEST
  std::unordered_map<int, int> mapa;
  std::map<int, int> mapa_ordered;
  LsmContainer<10, decltype(mapa_ordered)> cont_mapa_ordered("some_dir_ordered", std::move(mapa_ordered));
  LsmContainer<10, decltype(mapa)> cont("some_dir", std::move(mapa));
  int i = 0;
  while (i < 999999)
    i++;
  LsmContainer<10, decltype(mapa)> cont2(cont);
  i = 0;
  while (i < 999999)
    i++;

  LsmContainer<10, decltype(mapa)> cont3(std::move(cont));
#endif // CREATION_TEST

#ifdef ADD_TEST

  // using add_data_t = uint64_t;
  // using add_data_t = test_data_t;
  using add_data_t = std::string;
  using add_key_t = uint64_t;

  std::unordered_map<add_key_t, add_data_t> add_mapa;
  std::map<add_key_t, add_data_t> add_mapa_ordered;
  LsmContainer<1000, decltype(add_mapa)> add_cont_mapa("add_dir", std::move(add_mapa));
  LsmContainer<1000, decltype(add_mapa_ordered)> add_cont_mapa_ordered("add_dir_order", std::move(add_mapa_ordered));

  for (int i = 0; i < 2005; ++i) {
    // add_cont_mapa.Add({i, {UniqueNameGenerator::GetNumber(), UniqueNameGenerator::GetNumber()}});
    add_cont_mapa.Add({i, UniqueNameGenerator::GetString()});
  };

  for (int i = 0; i < 2005; ++i) {
    // add_cont_mapa_ordered.Add({i, {UniqueNameGenerator::GetNumber(), UniqueNameGenerator::GetNumber()}});
    add_cont_mapa_ordered.Add({i, UniqueNameGenerator::GetString()});
  }
#endif // ADD_TEST

#ifdef FIND_TEST
  // using add_data_t = uint64_t;
  using add_data_t = std::string;
  using add_key_t = std::string;
  // using add_key_t = key;
  // using add_key_t = uint64_t;

  std::unordered_map<add_key_t, add_data_t> add_mapa;
  std::map<add_key_t, add_data_t> add_mapa_ordered;
  LsmContainer<1000, decltype(add_mapa)> add_cont_mapa("add_dir", std::move(add_mapa));
  LsmContainer<1000, decltype(add_mapa_ordered)> add_cont_mapa_ordered("add_dir_order", std::move(add_mapa_ordered));

  for (int i = 0; i < 2005; ++i) {
    add_cont_mapa.Add({std::to_string(i), std::to_string(i)});
    // add_cont_mapa.Add({i, i});
    // add_cont_mapa.Add({i, UniqueNameGenerator::GetString()});
  };

  for (int i = 0; i < 2005; ++i) {
    add_cont_mapa_ordered.Add({std::to_string(i), std::to_string(i)});
    // add_cont_mapa_ordered.Add({i, i});
    // add_cont_mapa_ordered.Add({i, UniqueNameGenerator::GetString()});
  }

  std::cout << "\n====================================================\n";

  for (int i = 0; i < 2300; ++i) {
    if (auto search_res = add_cont_mapa.Find(std::to_string(i));
    // if (auto search_res = add_cont_mapa.Find(i);
      search_res.second) {
      std::cout << search_res.first;
    }
    std::cout << " <> ";
    if (auto search_res = add_cont_mapa_ordered.Find(std::to_string(i));
    // if (auto search_res = add_cont_mapa_ordered.Find(i);
      search_res.second) {
      std::cout << search_res.first;
    }
    std::cout << std::endl;
  }

  std::cout << "\n====================================================\n";
#endif // FIND_TEST

#ifdef REMOVE_TEST
  // using add_data_t = uint64_t;
  using add_data_t = std::string;
  using add_key_t = std::string;
  // using add_key_t = key;
  // using add_key_t = uint64_t;

  std::unordered_map<add_key_t, add_data_t> remove_mapa;
  std::map<add_key_t, add_data_t> remove_mapa_ordered;
  LsmContainer<100000, decltype(remove_mapa)> remove_cont_mapa("add_dir", std::move(remove_mapa));
  LsmContainer<100000, decltype(remove_mapa_ordered)> remove_cont_mapa_ordered("add_dir_order", std::move(remove_mapa_ordered));

  for (uint64_t i = 0; i < 9000000; ++i) {
    remove_cont_mapa.Add({std::to_string(i), std::to_string(i)});
    // remove_cont_mapa.Add({i, i});
    // remove_cont_mapa.Add({i, UniqueNameGenerator::GetString()});
  };

  std::cout << "map cont add done" << std::endl;

  for (uint64_t i = 0; i < 9000000; ++i) {
    remove_cont_mapa_ordered.Add({std::to_string(i), std::to_string(i)});
    // remove_cont_mapa_ordered.Add({i, i});
    // remove_cont_mapa_ordered.Add({i, UniqueNameGenerator::GetString()});
  }

  std::cout << "unordered map cont add done" << std::endl;

  std::cout << "\n====================================================\n";

  for (uint64_t i = 0; i < 19000000; ++i) {
    if (!(i % 100)) {
      std::cout << "remove: " << std::to_string(i) << std::endl;
    }
  // for (int i = 2300; i > -1; --i) {
    // unordered map
    if (remove_cont_mapa.Remove(std::to_string(i)) || i > 9000000) {
      // std::cout << "unordered map remove correct" << std::endl;
    } else {
      std::cout << "unordered map remove non-correct: " << i << std::endl;
    }

    // map
    if (remove_cont_mapa_ordered.Remove(std::to_string(i)) || i > 9000000) {
      // std::cout << "map remove correct" << std::endl;
    } else {
      std::cout << "map remove non-correct: " << i << std::endl;
    }

    // unordered map
    if (auto search_res = remove_cont_mapa.Find(std::to_string(i));
    // if (auto search_res = remove_cont_mapa.Find(i);
      search_res.second) {
      std::cout << "unordered map find non-correct: " << search_res.first << std::endl;
    } else {
      // std::cout << "unordered map find correct" << std::endl;
    }

    // map
    if (auto search_res = remove_cont_mapa_ordered.Find(std::to_string(i));
    // if (auto search_res = remove_cont_mapa_ordered.Find(i);
      search_res.second) {
      std::cout << "map find non-correct: " << search_res.first << std::endl;
    } else {
      // std::cout << "map find correct" << std::endl;
    }
  }

  std::cout << "\n====================================================\n";
#endif // REMOVE_TEST

#ifdef VECTOR_MURDERING
  using murder_data_t = std::string;
  using murder_key_t = std::string;
  std::unordered_map<murder_key_t, murder_data_t> std_cont;

  try {
    for (uint64_t i = 0; i < 9999999999; ++i) {
      for (uint64_t j = 0; j < 9999999999; ++j) {
        if (!(j % 1000000)) {
          std::cout << "correct insert" << std::to_string(i) << " " << std::to_string(j) << std::endl;
        }
        auto ins_res = std_cont.insert({std::to_string(i) + std::to_string(j),
          std::to_string(i) + std::to_string(j)});
        if (!ins_res.second) {
          std::cerr << "Insertion failed for key: " << std::to_string(i) + std::to_string(j) << std::endl;
        }
      }
    }
  } catch (std::bad_alloc& ex) {
    std::cout << "std::map loose(" << std::endl;
    std::cout << ex.what() << std::endl;
  }

#endif // VECTOR_MURDERING

#ifdef SIZE_TEST
  LsmContainer<1000, std::map<uint64_t, uint64_t>> 
    size_cont_mapa("size_dir_order", {});

  auto print_sizes = [&size_cont_mapa](){
    auto sizes = size_cont_mapa.Size();
    std::for_each(sizes.begin(), sizes.end(), [](uint64_t size){
      std::cout << size << " + ";
    });
    std::cout << std::endl;
  };

  for (uint64_t i = 0; i < 9323; ++i) {
    size_cont_mapa.Add({i, i % 100});
  };
  size_cont_mapa.Remove(345);
  std::cout << "remove done 345" << std::endl;
  size_cont_mapa.Remove(3443);
  std::cout << "remove done 345243" << std::endl;
  size_cont_mapa.Remove(328);
  std::cout << "remove done 34528" << std::endl;
  size_cont_mapa.Remove(563);
  std::cout << "remove done 563" << std::endl;
  size_cont_mapa.Remove(0);
  std::cout << "remove done 0" << std::endl;
  size_cont_mapa.Remove(1);
  std::cout << "remove done 1" << std::endl;
  size_cont_mapa.Remove(2);
  std::cout << "remove done 2" << std::endl;

  print_sizes();

  std::cout << "size test done" << std::endl;
#endif // SIZE_TEST

  return 0;
}