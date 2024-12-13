#include "get_width_event.hpp"

#include <iostream>
#include <sstream>
#include <string>

#include <event/event.hpp>
#include <game_device.hpp>

namespace battleship {

GetWidth::~GetWidth() {  };

void GetWidth::Run() {  };

ExecuteStatus GetWidth::Execute(InputDevice&, ExecuteAdditionalArgument& arg) {
  GameDevice& game_device = dynamic_cast<GameDevice&>(arg);

  if (game_device.GetRole() != GameDevice::Role::MASTER)
    return ExecuteStatus::EXECUTE_FAIL;

  std::cout << game_device.GetConfig().field_w_ << std::endl;

  return ExecuteStatus::CORRECT;
};

} // battleship