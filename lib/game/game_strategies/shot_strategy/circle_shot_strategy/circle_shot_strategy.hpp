#ifndef _CIRCLE_SHOT_STRATEGY_HPP_
#define _CIRCLE_SHOT_STRATEGY_HPP_

#include "../shot_strategy.hpp"

#include <cstdint>
#include <utility>

#include <game_config/game_config.hpp>

namespace battleship {

class CircleShotStrategy : public ShotStrategyBase {
 public:
  CircleShotStrategy(GameConfig cfg);
  std::pair<uint64_t, uint64_t> GetShot() override;
  ~CircleShotStrategy() override = default;
 private:
  uint64_t x = 0, y = 0;
  uint64_t max_x = 0, max_y = 0;
  uint64_t prev_max_x = 0, prev_max_y = 0;
  bool reverse_x = false, reverse_y = false;
  bool is_x_move = true;
};

} // battleship

#endif // _CIRCLE_SHOT_STRATEGY_HPP_