#ifndef _SHIP_HPP_
#define _SHIP_HPP_

#include <cstdint>
#include <fstream>
#include <array>
#include <type_traits>
#include <utility>
#include <map>

#include <ship_coordinates/ship_coordinates.hpp>
#include <lsm_container.hpp>

namespace battleship {

class Ship {
 public:
  using CoordType = uint64_t;

 public:
  Ship();

  template<typename CoordT, typename LenghtT>
  requires(std::is_convertible_v<CoordType, CoordT> && std::is_convertible_v<int32_t, LenghtT>)
  Ship(CoordT x, CoordT y, bool rotate, LenghtT lenght) : 
     x_(static_cast<CoordType>(x)), y_(static_cast<CoordType>(y)) {
    if (rotate) {
      data_ |= kRotateBit;
    }

    if (static_cast<int32_t>(lenght) - 1 < kLengthBitCont.size()) {
      data_ |= kLengthBitCont[static_cast<int32_t>(lenght) - 1];
    }
  };

 public:
  inline int32_t GetLenght() const { return ((data_ & kLengthMask) >> 5) + 1; }
  inline std::pair<CoordType, CoordType> GetRootCoord() const { return {x_, y_}; }
  inline bool IsRotate() const { return (data_ & kRotateMask) >> 7; }
  inline bool IsLive() const { return Hp() != 0; };
  inline int32_t Hp() const {
    int32_t hp = GetLenght();

    for (auto&& elem : kHitBitCont) {
      if (data_ & elem) {
        --hp;
      }
    }

    return hp;
  };

 public:
  ShipCoord CreateCoordinates();
  bool Hit(CoordType x, CoordType y);

 public:
  friend std::ostream& operator<<(std::ostream& stream, const Ship& ship);
  friend std::istream& operator>>(std::istream& stream, Ship& ship);

 private:
  static constexpr char kRotateBit = 0b10000000;
  static constexpr std::array<char, 4> kLengthBitCont = {
    0b00000000,
    0b00100000,
    0b01000000,
    0b01100000,
  };
  static constexpr std::array<char, 4> kHitBitCont = {
    0b00010000,
    0b00001000,
    0b00000100,
    0b00000010,
  };

 private:
  static constexpr char kRotateMask = 0b10000000;
  static constexpr char kLengthMask = 0b01100000;
  static constexpr char kHitsMask = 0b00011110;

 private:
  CoordType x_;
  CoordType y_;
  uint8_t data_ = 0;
};

namespace {

using ShipContainerType = LsmContainer<100000000, std::map<ShipCoord, Ship>>;

} // namespace

} // battleship

#endif // _SHIP_HPP_