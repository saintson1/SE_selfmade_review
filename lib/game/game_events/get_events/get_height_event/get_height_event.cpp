#include "get_height_event.hpp"

#include <iostream>
#include <sstream>
#include <string>

#include <event/event.hpp>
#include <game_device.hpp>

namespace battleship {

GetHeight::~GetHeight() {  };

void GetHeight::Run() {  };

ExecuteStatus GetHeight::Execute(InputDevice& input, ExecuteAdditionalArgument& arg) {
  GameDevice& game_device = dynamic_cast<GameDevice&>(arg);

if (game_device.GetRole() != GameDevice::Role::MASTER)    return ExecuteStatus::EXECUTE_FAIL;

  std::cout << game_device.GetConfig().field_h_ << std::endl;
  return ExecuteStatus::CORRECT;
};

} // battleship