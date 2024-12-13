#include "config_validator.hpp"

namespace battleship {

ConfigValidatorBase::ConfigValidatorBase(GameConfig cfg) : cfg_(cfg) {  };

ConfigValidatorBase::~ConfigValidatorBase() {  };

} // battleship