#include <iostream>

#include "unique_name_generator.hpp"

int main(int, char**) {
  std::cout << battleship::UniqueNameGenerator::GetString() << std::endl;
  std::cout << battleship::UniqueNameGenerator::GetNumber() << std::endl;

  return 0;
}