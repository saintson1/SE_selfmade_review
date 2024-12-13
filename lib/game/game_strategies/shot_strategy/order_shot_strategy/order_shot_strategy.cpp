#include "order_shot_strategy.hpp"

namespace battleship {

OrderShotStrategy::OrderShotStrategy(GameConfig cfg) : ShotStrategyBase(cfg) {  };

std::pair<uint64_t, uint64_t> OrderShotStrategy::GetShot() {
  if (x + 1 == cfg_.field_w_)
    x = 0, ++y;

  if (y == cfg_.field_h_)
    y = 0, x = 0;

  return {x++, y};
};

}  // battleship