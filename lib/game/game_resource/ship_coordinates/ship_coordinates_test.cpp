#include <cstdint>
#include <iostream>
#include <type_traits>
#include <utility>
#include <concepts>

#include "ship_coordinates.hpp"
#include "ship_coordinates/ship_coordinates.hpp"
#include <ship/ship.hpp>

using namespace battleship;


namespace battleship {

} // battleship

int main(int, char**) {
  Ship ship2{1, 1, true, 2};
  Ship ship3{4, 2, false, 3};


  ShipCoord coord2 = ship2.CreateCoordinates();
  ShipCoord coord3 = ship3.CreateCoordinates();

  if (coord2 == std::pair<uint64_t, uint64_t>{1, 2}) {
    std::cout << "eq" << std::endl;
  } else {
    std::cout << "not eq" << std::endl;
  }
  if (coord2 == std::pair<uint64_t, uint64_t>{1, 1}) {
    std::cout << "eq" << std::endl;
  } else {
    std::cout << "not eq" << std::endl;
  }
  if (coord2 == std::pair<uint64_t, uint64_t>{1, 3}) {
    std::cout << "eq" << std::endl;
  } else {
    std::cout << "not eq" << std::endl;
  }
  if (coord2 == std::pair<uint64_t, uint64_t>{1, 4}) {
    std::cout << "eq" << std::endl;
  } else {
    std::cout << "not eq" << std::endl;
  }
  if (std::pair<uint64_t, uint64_t>{2, 1} > coord2) {
    std::cout << "eq" << std::endl;
  } else {
    std::cout << "not eq" << std::endl;
  }

  auto pair_coord = std::pair<uint64_t, uint64_t>{1, 1};

  return 0;
}