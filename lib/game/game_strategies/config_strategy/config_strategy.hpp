#ifndef _CONFIG_STRATEGY_HPP_
#define _CONFIG_STRATEGY_HPP_

#include <concepts>
#include <memory>

#include <game_config/game_config.hpp>
#include <game_resource/ship/ship.hpp>
#include <game_resource/ship_coordinates/ship_coordinates.hpp>

namespace battleship {

template<typename T>
concept IsConfigStrategy = requires() {
  {T::Get()} -> std::same_as<std::pair<GameConfig, ShipContainerType>>;
};

struct ConfigStrategyClassic {
  static std::pair<GameConfig, ShipContainerType> Get();
};

struct ConfigStrategySingleTon {
  static std::pair<GameConfig, ShipContainerType> Get();
};

} // battleship

#endif // _CONFIG_STRATEGY_HPP_