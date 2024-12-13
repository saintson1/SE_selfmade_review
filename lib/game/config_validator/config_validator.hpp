#ifndef _CONFIG_VALIDATOR_HPP_
#define _CONFIG_VALIDATOR_HPP_

#include <game_config/game_config.hpp>
#include <ship/ship.hpp>

namespace battleship {

class ConfigValidatorBase {
 public:
  ConfigValidatorBase(GameConfig cfg);
  virtual  ShipContainerType Place() = 0;
  virtual bool IsValid() = 0;
  virtual ~ConfigValidatorBase() = 0;
 protected:
  GameConfig cfg_;
};

} // battleship

#endif // _CONFIG_VALIDATOR_HPP_