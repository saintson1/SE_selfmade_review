#include "ship_coordinates.hpp"

#include <compare>
#include <cstddef>
#include <iostream>

namespace battleship {

ShipCoord::ShipCoord(std::initializer_list<CoordType> coords) :
  coords_(std::move(coords)){  };

ShipCoord::ShipCoord(std::vector<CoordType>&& coords) :
  coords_(std::move(coords)) {  };

ShipCoord::ShipCoord(const ShipCoord& value) :
  coords_(value.coords_) {  };

ShipCoord::ShipCoord(ShipCoord&& value) :
  coords_(std::move(value.coords_)) {  };

ShipCoord& ShipCoord::operator=(const ShipCoord& value) {
  if (this == &value)
    return *this;

  coords_ = value.coords_;

  return *this;
};

ShipCoord& ShipCoord::operator=(ShipCoord&& value) {
  if (this == &value)
    return *this;

  coords_ = std::move(value.coords_);

  return *this;
};

std::strong_ordering ShipCoord::operator<=>(const ShipCoord& rhs) const {
  if (typeid(rhs) == typeid(const SinglShipCoord&))
    return *this <=> dynamic_cast<const SinglShipCoord&>(rhs);

  if (!coords_.size() && !rhs.coords_.size())
    return std::strong_ordering::equal;

  if (!coords_.size())
    return std::strong_ordering::less;

  if (!rhs.coords_.size())
    return std::strong_ordering::greater;

  if (coords_[0].second < rhs.coords_[0].second) {
    return std::strong_ordering::less;
  } else if (coords_[0].second > rhs.coords_[0].second) {
    return std::strong_ordering::greater;
  } else {
    if (coords_[0].first < rhs.coords_[0].first) {
      return std::strong_ordering::less;
    } else if (coords_[0].first > rhs.coords_[0].first) {
      return std::strong_ordering::greater;
    } else {
      return std::strong_ordering::equal;
    }
  }
};

std::strong_ordering ShipCoord::operator<=>(const SinglShipCoord& rhs) const {
  if (!coords_.size())
    return std::strong_ordering::less;

  if (std::find_if(coords_.begin(), coords_.end(),
    [&rhs](const CoordType& coord){
    if (coord.first == rhs.GetCoord().first && coord.second == rhs.GetCoord().second) {
      return true;
    }
    return false;
  }) != coords_.end()) {
    return std::strong_ordering::equal;
  };

  if (coords_[0].second < rhs.GetCoord().second) {
    return std::strong_ordering::less;
  } else if (coords_[0].second > rhs.GetCoord().second) {
    return std::strong_ordering::greater;
  } else {
    if (coords_[0].first < rhs.GetCoord().first) {
      return std::strong_ordering::less;
    } else if (coords_[0].first > rhs.GetCoord().first) {
      return std::strong_ordering::greater;
    } else {
      return std::strong_ordering::equal;
    }
  }
};

bool ShipCoord::operator==(const ShipCoord& rhs) const {
  if (typeid(rhs) == typeid(const SinglShipCoord&))
    return *this == dynamic_cast<const SinglShipCoord&>(rhs);

  if (!coords_.size() && !rhs.coords_.size())
    return true;

  if (!coords_.size())
    return false;

  if (!rhs.coords_.size())
    return false;

  if (coords_[0].second == rhs.coords_[0].second) {
    if (coords_[0].first == rhs.coords_[0].first) {
      return true;
    }
  }

  return false;
};

bool ShipCoord::operator==(const SinglShipCoord& rhs) const {
  if (!coords_.size())
    return false;

  if (std::find_if(coords_.begin(), coords_.end(),
    [&rhs](const CoordType& coord){
    if (coord.first == rhs.GetCoord().first && coord.second == rhs.GetCoord().second) {
      return true;
    }
    return false;
  }) != coords_.end()) {
    return true;
  };

  return false;
};

std::ostream& operator<<(std::ostream& stream, const ShipCoord& value) {
  if (value.coords_.size()) {
    stream.put('y');
    auto size = value.coords_.size();
    stream.write(reinterpret_cast<char*>(&size), sizeof(size));
  } else {
    stream.put('n');
  }

  for (auto coord : value.coords_) {
    stream.write(reinterpret_cast<char*>(&coord.first), sizeof(coord.first));
  };

  return stream;
};

std::istream& operator>>(std::istream& stream, ShipCoord& value) {
  char ch;
  stream.get(ch);

  auto size = value.coords_.size();
  if (ch == 'y') {
    stream.read(reinterpret_cast<char*>(&size), sizeof(size));
  } else if (ch == 'n') {
    value = ShipCoord{};
    return stream;
  } else {
    return stream;
  }

  value.coords_ = decltype(value.coords_)(size);
  for (auto coord : value.coords_) {
    stream.read(reinterpret_cast<char*>(&coord.first), sizeof(coord.first));
  };

  return stream;
};

SinglShipCoord::SinglShipCoord(const ShipCoord::CoordType& coord) : coord_(coord) {  };

SinglShipCoord::~SinglShipCoord() {  };

std::strong_ordering SinglShipCoord::operator<=>(const SinglShipCoord& rhs) const {
  if (coord_.second < rhs.coord_.second) {
    return std::strong_ordering::less;
  } else if (coord_.second > rhs.coord_.second) {
    return std::strong_ordering::greater;
  } else {
    if (coord_.first < rhs.coord_.first) {
      return std::strong_ordering::less;
    } else if (coord_.first > rhs.coord_.first) {
      return std::strong_ordering::greater;
    } else {
      return std::strong_ordering::equal;
    }
  }
};

std::strong_ordering SinglShipCoord::operator<=>(const ShipCoord& rhs) const {
  std::strong_ordering cmp_res = rhs <=> *this;
  if (cmp_res == std::strong_ordering::greater)
    return std::strong_ordering::less;
  if (cmp_res == std::strong_ordering::less)
    return std::strong_ordering::greater;
  return std::strong_ordering::equal;
};

bool SinglShipCoord::operator==(const SinglShipCoord& rhs) const {
  return coord_.first == rhs.coord_.first && coord_.second == rhs.coord_.second;
};

bool SinglShipCoord::operator==(const ShipCoord& rhs) const {
  return rhs == *this;
};

} // battleship
