#ifndef _SHOT_STRATEGY_HPP_
#define _SHOT_STRATEGY_HPP_

#include <cstdint>
#include <utility>

#include <game_config/game_config.hpp>
#include <game_resource/shot/shot.hpp>

namespace battleship {

class ShotStrategyBase {
 public:
  ShotStrategyBase(const GameConfig& cfg);
  virtual ~ShotStrategyBase() = 0;
 public:
  virtual std::pair<uint64_t, uint64_t> GetShot() = 0;
  virtual void GetResult(ShotState state);
 protected:
  GameConfig cfg_;
};

} // battleship

#endif // _SHOT_STRATEGY_HPP_