#include "config_strategy.hpp"

#include <memory>
#include <array>

#include <game_config/game_config.hpp>
#include <game_resource/ship/ship.hpp>
#include <game_resource/ship_coordinates/ship_coordinates.hpp>
#include <unique_name_generator.hpp>

namespace battleship {

std::pair<GameConfig, ShipContainerType> ConfigStrategyClassic::Get() {
  GameConfig cfg(10, 10);
  cfg.ship_counts_ = {4, 3, 2, 1};

  ShipContainerType cont("battleship_classic", {
    {{{0, 5}, {1, 5}, {2, 5}, {3, 5}}, {0, 5, false, 4}},
    {{{3, 1}, {3, 2}, {3, 3}}, {3, 1, true, 3}},
    {{{6, 7}, {6, 8}, {6, 9}}, {6, 7, true, 3}},
    {{{6, 2}, {6, 3}}, {6, 2, true, 2}},
    {{{8, 2}, {8, 3}}, {8, 2, true, 2}},
    {{{9, 5}, {9, 6}}, {9, 5, true, 2}},
    {{{0, 2}}, {0, 2, false, 1}},
    {{{7, 2}}, {7, 2, false, 1}},
    {{{5, 7}}, {5, 7, false, 1}},
    {{{9, 9}}, {9, 9, false, 1}},
  });

  return {cfg, std::move(cont)};
};

std::pair<GameConfig, ShipContainerType> ConfigStrategySingleTon::Get() {
  GameConfig cfg(8, 8);
  cfg.ship_counts_ = {0, 0, 0, 8};

  ShipContainerType cont("battleship_singleton", {
    {{{0, 0}, {1, 0}, {2, 0}, {3, 0}}, {0, 0, false, 4}},
    {{{0, 2}, {1, 2}, {2, 2}, {3, 2}}, {0, 0, false, 4}},
    {{{4, 5}, {5, 5}, {6, 5}, {7, 5}}, {4, 5, false, 4}},
    {{{4, 7}, {5, 7}, {6, 7}, {7, 7}}, {4, 7, false, 4}},
    {{{0, 4}, {0, 5}, {0, 6}, {0, 7}}, {0, 4, true, 4}},
    {{{2, 4}, {2, 5}, {2, 6}, {2, 7}}, {2, 4, true, 4}},
    {{{5, 0}, {5, 1}, {5, 2}, {5, 3}}, {5, 0, true, 4}},
    {{{7, 0}, {7, 1}, {7, 2}, {7, 3}}, {5, 0, true, 4}},
  });


  return {cfg, std::move(cont)};
};

} // battleship