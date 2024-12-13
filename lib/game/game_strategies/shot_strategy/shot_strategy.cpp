#include "shot_strategy.hpp"

#include <game_config/game_config.hpp>
#include <game_resource/shot/shot.hpp>

namespace battleship {

ShotStrategyBase::ShotStrategyBase(const GameConfig& cfg) : cfg_(cfg) {  };

ShotStrategyBase::~ShotStrategyBase() {  };

void ShotStrategyBase::GetResult(ShotState state) {  };

} // battleship