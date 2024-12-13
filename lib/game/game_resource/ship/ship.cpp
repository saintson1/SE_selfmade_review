#include "ship.hpp"

#include <cstdint>
#include <iostream>
#include <memory>
#include <utility>

#include <ship_coordinates/ship_coordinates.hpp>

namespace battleship {

Ship::Ship() : x_(0), y_(0), data_(0) {  };

namespace {

template<typename Type>
Type AbsDiff(const Type& lhs, const Type& rhs) {
  return lhs > rhs ? lhs - rhs : rhs - lhs;
};

} // namespace

bool Ship::Hit(CoordType x, CoordType y) {
  auto lenght = GetLenght();
  if (AbsDiff(x_, x) >= lenght || AbsDiff(y_, y) >= lenght)
    return false;

  auto rotate = IsRotate();
  if (rotate) {
    if (x_ != x) {
      return false;
    }
    auto tmp = AbsDiff(x_, x);
    data_ |= kHitBitCont[AbsDiff(y_, y)];
    return true;
  } else {
    if (y_ != y) {
      return false;
    }
    auto tmp = AbsDiff(x_, x);
    data_ |= kHitBitCont[AbsDiff(x_, x)];
    return true;
  }

  return true;
};

std::ostream& operator<<(std::ostream& stream, const Ship& ship) {
  stream.write(reinterpret_cast<const char*>(&ship.x_), sizeof(ship.x_));
  stream.write(reinterpret_cast<const char*>(&ship.y_), sizeof(ship.y_));
  stream.write(reinterpret_cast<const char*>(&ship.data_), sizeof(ship.data_));
  return stream;
};

std::istream& operator>>(std::istream& stream, Ship& ship) {
  stream.read(reinterpret_cast<char*>(&ship.x_), sizeof(ship.x_));
  stream.read(reinterpret_cast<char*>(&ship.y_), sizeof(ship.y_));
  stream.read(reinterpret_cast<char*>(&ship.data_), sizeof(ship.data_));
  return stream;
};

ShipCoord Ship::CreateCoordinates() {
  std::vector<ShipCoord::CoordType> comput_coord_cont(GetLenght());

  CoordType root_offset = 0;
  if (IsRotate()) {
    for (auto&& coord : comput_coord_cont) {
      coord = {x_, y_ + root_offset};
      ++root_offset;
    }
  } else {
    for (auto&& coord : comput_coord_cont) {
      coord = {x_ + root_offset, y_};
      ++root_offset;
    }
  }

  return {std::move(comput_coord_cont)};
};

} // battleship