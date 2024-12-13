#ifndef _CHESS_ORDER_SHOT_STRATEGY_HPP_
#define _CHESS_ORDER_SHOT_STRATEGY_HPP_

#include "../shot_strategy.hpp"

#include <cstdint>
#include <utility>

#include <game_config/game_config.hpp>


namespace battleship {

class ChessOrderShotStrategy : public ShotStrategyBase {
 public:
  ChessOrderShotStrategy(GameConfig cfg);
  std::pair<uint64_t, uint64_t> GetShot() override;
  ~ChessOrderShotStrategy() override = default;
 private:
  uint64_t x = 0, y = 0;
  bool scd_move = false;
};

} // battleship

#endif // _CHESS_ORDER_SHOT_STRATEGY_HPP_