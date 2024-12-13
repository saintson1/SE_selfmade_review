#ifndef _UNIQUE_NAME_GENERATOR_HPP_
#define _UNIQUE_NAME_GENERATOR_HPP_

#include <cstdint>
#include <string>

namespace battleship {

class UniqueNameGenerator {
 public:
  static std::string GetString();
  static uint64_t GetNumber();
};

} // battlehship

#endif // _UNIQUE_NAME_GENERATOR_HPP_