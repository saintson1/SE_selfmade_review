#ifndef _ORDER_SHOT_STRATEGY_HPP_
#define _ORDER_SHOT_STRATEGY_HPP_

#include "../shot_strategy.hpp"

#include <cstdint>
#include <utility>

#include <game_config/game_config.hpp>


namespace battleship {

class OrderShotStrategy : public ShotStrategyBase {
 public:
  OrderShotStrategy(GameConfig cfg);
  std::pair<uint64_t, uint64_t> GetShot() override;
  ~OrderShotStrategy() override = default;
 private:
  uint64_t x = 0, y = 0;
};

} // battleship

#endif // _ORDER_SHOT_STRATEGY_HPP_