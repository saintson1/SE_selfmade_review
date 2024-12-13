#ifndef _LINE_VALIDATOR_HPP_
#define _LINE_VALIDATOR_HPP_

#include <game_config/game_config.hpp>
#include <ship/ship.hpp>
#include "../config_validator.hpp"

namespace battleship {

class LineValidator : public ConfigValidatorBase {
 public:
  LineValidator(GameConfig cfg);
  ShipContainerType Place() override;
  bool IsValid() override;
  ~LineValidator() override;
};

} // battleship

#endif // _LINE_VALIDATOR_HPP_