#include "circle_shot_strategy.hpp"

namespace battleship {

CircleShotStrategy::CircleShotStrategy(GameConfig cfg) :
  ShotStrategyBase(cfg), max_x(cfg.field_w_), max_y(cfg.field_h_),
    prev_max_x(cfg.field_w_), prev_max_y(cfg.field_h_) {  };

std::pair<uint64_t, uint64_t> CircleShotStrategy::GetShot() {

  if (is_x_move) {
    if (!reverse_x) {
      if (x == max_x) {
        prev_max_x = max_x - 1;
        if (max_x == cfg_.field_w_) {
          max_x = 0;
        }
        max_x = cfg_.field_w_ - prev_max_x - 1;
        is_x_move = !is_x_move;
        reverse_x = !reverse_x;
      } else {
        x++;
      }
    } else {
      if (x == max_x) {
        prev_max_x = max_x - 1;
        if (max_x == cfg_.field_w_) {
          max_x = 0;
        }
        max_x = cfg_.field_w_ - prev_max_x - 1;
        is_x_move = !is_x_move;
        reverse_x = !reverse_x;
      } else {
        x--;
      }
    }
  } else {
    if (!reverse_y) {
      if (y == max_y) {
        prev_max_y = max_y - 1;
        if (max_y == cfg_.field_h_) {
          max_y = 0;
        }
        max_y = cfg_.field_h_ - prev_max_y - 1;
        is_x_move = !is_x_move;
        reverse_y = !reverse_y;
      } else {
        y++;
      }
    } else {
      if (y == max_y) {
        prev_max_y = max_y - 1;
        if (max_y == cfg_.field_h_) {
          max_y = 0;
        }
        max_y = cfg_.field_h_ - prev_max_y - 1;
        is_x_move = !is_x_move;
        reverse_y = !reverse_y;
      } else {
        y--;
      }
    }
  }

  return {x, y};
};

}  // battleship