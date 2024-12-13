#ifndef _SHIP_COORDINATES_HPP_
#define _SHIP_COORDINATES_HPP_

#include <initializer_list>
#include <utility>
#include <vector>
#include <compare>
#include <iostream>

namespace battleship {

class SinglShipCoord;

class ShipCoord {
 public:
  using CoordType = std::pair<uint64_t, uint64_t>;

 public:
  ShipCoord() = default;
  ShipCoord(std::initializer_list<CoordType> coords);
  ShipCoord(std::vector<CoordType>&& coords);
  ShipCoord(const ShipCoord& value);
  ShipCoord(ShipCoord&& value);
  ShipCoord& operator=(const ShipCoord& value);
  ShipCoord& operator=(ShipCoord&& value);

  virtual ~ShipCoord() = default;

 public:
  virtual std::strong_ordering operator<=>(const ShipCoord& rhs) const;
  virtual std::strong_ordering operator<=>(const SinglShipCoord& rhs) const;
  virtual bool operator==(const ShipCoord& rhs) const;
  virtual bool operator==(const SinglShipCoord& rhs) const;

  friend std::ostream& operator<<(std::ostream& stream, const ShipCoord& value);
  friend std::istream& operator>>(std::istream& stream, ShipCoord& value);

 private:
  std::vector<CoordType> coords_;
};

class SinglShipCoord : public ShipCoord {
 public:
  SinglShipCoord() = default;
  SinglShipCoord(const ShipCoord::CoordType& coord);
  SinglShipCoord(const SinglShipCoord&) = default;
  ~SinglShipCoord() override;

 public:
  std::strong_ordering operator<=>(const SinglShipCoord& rhs) const override;
  std::strong_ordering operator<=>(const ShipCoord& rhs) const override;
  bool operator==(const SinglShipCoord& rhs) const override;
  bool operator==(const ShipCoord& rhs) const override;

 public:
  inline ShipCoord::CoordType GetCoord() const { return coord_; };

 private:
  ShipCoord::CoordType coord_;
};

} // battleship

#endif // _SHIP_COORDINATES_HPP_