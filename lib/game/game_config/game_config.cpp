#include "game_config.hpp"

namespace battleship {

GameConfig::GameConfig(FieldSize w, FieldSize h) :
  field_w_(w), field_h_(h) {  };

GameConfig::~GameConfig() {  };

bool GameConfig::IsValid() {
  if (field_h_ == 0 || field_w_== 0) {
    return false;
  }

  return true;
};

} // battleship