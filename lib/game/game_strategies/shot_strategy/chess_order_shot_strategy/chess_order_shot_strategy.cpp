#include "chess_order_shot_strategy.hpp"

namespace battleship {

ChessOrderShotStrategy::ChessOrderShotStrategy(GameConfig cfg) : ShotStrategyBase(cfg) {  };

std::pair<uint64_t, uint64_t> ChessOrderShotStrategy::GetShot() {
  if (x >= cfg_.field_w_) {
    if (scd_move) {
      if (y % 2) {
        x = 1;
      } else {
        x = 0;
      }
    } else {
      if (y % 2) {
        x = 0;
      } else {
        x = 1;
      }
    }
    y += 1;
  }

  if (y >= cfg_.field_h_) {
    y = 0;
    if (scd_move) {
      x = 0;
    } else {
      x = 1;
    }
    scd_move = !scd_move;
  }
  x += 2;

  return {x - 2, y};
};

}  // battleship