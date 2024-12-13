#include "unique_name_generator.hpp"

#include <string>
#include <chrono>

namespace battleship {

std::string UniqueNameGenerator::GetString() {
  return std::to_string(UniqueNameGenerator::GetNumber());
};

uint64_t UniqueNameGenerator::GetNumber() {
  using namespace std::chrono;

  auto current_time = system_clock::now();
  auto now_ms = time_point_cast<milliseconds>(current_time);
  auto epoch = now_ms.time_since_epoch();
  auto value = duration_cast<milliseconds>(epoch);

  return value.count();
};


} // battleship