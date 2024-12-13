#include "line_validator.hpp"

#include <cstdint>
#include <vector>
#include <algorithm>
#include <list>

#include <ship/ship.hpp>
#include <game_config/game_config.hpp>
#include "../config_validator.hpp"

namespace battleship {

LineValidator::LineValidator(GameConfig cfg) :
  ConfigValidatorBase(cfg) {  };

bool LineValidator::IsValid() {
  decltype(cfg_)::FieldSize max_x = std::max(cfg_.field_w_, cfg_.field_h_);
  decltype(cfg_)::FieldSize max_y = std::min(cfg_.field_w_, cfg_.field_h_);

  std::list<char> remainder_cont;

  decltype(cfg_)::FieldSize x_count = 0;
  decltype(cfg_)::FieldSize y_count = 0;

  auto ship_counts_ = cfg_.ship_counts_;

  bool is_done = true;

  for (size_t ship_type = ship_counts_.size(), end_type = -1;
    ship_type - 1 != end_type; ship_type--) {
    while (ship_counts_[ship_type - 1]) {
      if (x_count + ship_type > max_x) {
        if (max_x - (x_count - 1)) {
          remainder_cont.push_back(max_x - x_count);
        } else {
          remainder_cont.push_back(max_x - (x_count - 1));
        }
        if (y_count + 2 >= max_y) {
          x_count = 0;
          break;
        } else {
          y_count += 2;
          x_count = 0;
        }
      } else {
        x_count += ship_type + 1;
        --ship_counts_[ship_type - 1];
      }
    }

    if (y_count + 2 >= max_y && x_count == 0) {
      if (ship_type - 1 == end_type && ship_counts_[ship_type - 1] == 0)
        is_done = false;
      break;
    }
  }

  if (is_done)
    return true;
  if (!is_done && remainder_cont.empty())
    return false;

  for (auto beg = ++remainder_cont.begin(), end = remainder_cont.end();
    beg != end; ++beg) {
    auto prev_itr = --beg;
    ++beg;
    remainder_cont.insert(beg, std::min(*prev_itr, *beg));
  }
  if (!(max_y % 2))
    remainder_cont.push_back(remainder_cont.back());

  auto block_find = 
    [&remainder_cont](decltype(remainder_cont)::iterator& begin) {
      size_t block_lenght = 0;
      while (begin != remainder_cont.end() && *begin != 0) {
        *begin = *begin < 1 ? 0 : *begin -= 2;
        ++begin;
        ++block_lenght;
      }

      if (!block_lenght) {
        begin = remainder_cont.begin();
        while (begin != remainder_cont.end() && *begin != 0) {
          --*begin;
          ++begin;
          ++block_lenght;
        }
      }

      return block_lenght;
    };

  auto remainder_cont_itr = remainder_cont.begin();
  size_t block_lenght = block_find(remainder_cont_itr);

  for (size_t ship_type = ship_counts_.size(), end_type = 0;
    ship_type != end_type; --ship_type) {
    while (ship_counts_[ship_type - 1]) {
      // lenght count
      if (block_lenght < ship_type) {
        for (size_t less_type = block_lenght; less_type > 0; --less_type) {
          while (ship_counts_[less_type - 1]) {
            if (less_type <= block_lenght) {
              block_lenght -= less_type + 1;
              --ship_counts_[less_type - 1];
            } else {
              break;
            }
          }
        }
         block_lenght = block_find(remainder_cont_itr);
         if (block_lenght == 0) {
           return false;
         }
      } else {
        if (block_lenght - ship_type) {
          block_lenght -= ship_type + 1;
        } else {
          block_lenght -= ship_type;
        }
        --ship_counts_[ship_type - 1];
      }
    }
  }

  return true;
};

ShipContainerType LineValidator::Place() {
  ShipContainerType ship_cont{"line_validator_cont", {}};

  decltype(cfg_)::FieldSize max_x = std::max(cfg_.field_w_, cfg_.field_h_);
  decltype(cfg_)::FieldSize max_y = std::min(cfg_.field_w_, cfg_.field_h_);

  std::list<char> remainder_cont;

  decltype(cfg_)::FieldSize x_count = 0;
  decltype(cfg_)::FieldSize y_count = 0;

  auto ship_counts_ = cfg_.ship_counts_;

  bool is_done = true;

  for (size_t ship_type = ship_counts_.size(), end_type = -1;
    ship_type - 1 != end_type; ship_type--) {
    while (ship_counts_[ship_type - 1]) {
      if (x_count + ship_type > max_x) {
        if (max_x - (x_count - 1)) {
          remainder_cont.push_back(max_x - x_count);
        } else {
          remainder_cont.push_back(max_x - (x_count - 1));
        }
        if (y_count + 2 >= max_y) {
          x_count = 0;
          break;
        } else {
          y_count += 2;
          x_count = 0;
        }
      } else {
        Ship ship(x_count, y_count, false, ship_type);
        ship_cont.Add({ship.CreateCoordinates(), ship});

        x_count += ship_type + 1;
        --ship_counts_[ship_type - 1];
      }
    }

    if ((y_count + 2 >= max_y && x_count == 0 && max_y > 2) || (max_y < 2 && y_count != 0)) {
      if (ship_type - 1 == end_type && ship_counts_[ship_type - 1] == 0)
        is_done = false;
      break;
    }
  }

  if (is_done)
    return ship_cont;

  for (auto beg = ++remainder_cont.begin(), end = remainder_cont.end();
    beg != end; ++beg) {
    auto prev_itr = --beg;
    ++beg;
    remainder_cont.insert(beg, std::min(*prev_itr, *beg));
  }
  if (!(max_y % 2))
    remainder_cont.push_back(remainder_cont.back());

  x_count = max_x;
  y_count = 0;
  auto block_find = 
    [&remainder_cont, &x_count, &max_x, &y_count, &max_y](decltype(remainder_cont)::iterator& begin) {
      size_t block_lenght = 0;
      while (begin != remainder_cont.end() && *begin != 0) {
        ++y_count;
        *begin = *begin < 1 ? 0 : *begin -= 2;
        ++begin;
        ++block_lenght;
      }

      if (!block_lenght) {
        begin = remainder_cont.begin();
        --x_count;
        y_count = 0;
        while (begin != remainder_cont.end() && *begin != 0) {
          --*begin;
          ++begin;
          ++block_lenght;
          ++y_count;
        }
      }

      return block_lenght;
    };

  auto remainder_cont_itr = remainder_cont.begin();
  size_t block_lenght = block_find(remainder_cont_itr);

  for (size_t ship_type = ship_counts_.size(), end_type = 0;
    ship_type != end_type; --ship_type) {
    while (ship_counts_[ship_type - 1]) {
      // lenght count
      if (block_lenght < ship_type) {
        for (size_t less_type = block_lenght; less_type > 0; --less_type) {
          while (ship_counts_[less_type - 1]) {
            if (less_type <= block_lenght) {
              block_lenght -= less_type + 1;
              Ship ship(x_count, y_count, true, less_type);
              ship_cont.Add({ship.CreateCoordinates(), ship});
              // --ship_counts_[less_type - 1];
            } else {
              break;
            }
          }
        }
      } else {
        if (block_lenght - ship_type) {
          block_lenght -= ship_type + 1;
        } else {
          block_lenght -= ship_type;
        }
        Ship ship(x_count, y_count, true, ship_type);
        ship_cont.Add({ship.CreateCoordinates(), ship});
        // --ship_counts_[ship_type - 1];
      }
    }
  }

  return ship_cont;
};

LineValidator::~LineValidator() {  };

} // battleship