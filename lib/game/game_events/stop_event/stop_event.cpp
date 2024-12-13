#include "stop_event.hpp"

#include <iostream>
#include <memory>

#include <game_device/game_device.hpp>
#include <event.hpp>

#include <line_validator/line_validator.hpp>

#include <config_strategy/config_strategy.hpp>

namespace battleship {

Stop::~Stop() {  };

void Stop::Run() {
  std::cout << "ok" << std::endl;
};

ExecuteStatus Stop::Execute(InputDevice&, ExecuteAdditionalArgument& arg) {
  GameDevice& game_device = dynamic_cast<GameDevice&>(arg);

  if (game_device.GetState() != GameDevice::State::PREPARATION) {
    game_device.Reset();
  }
  
  Run();

  return ExecuteStatus::CORRECT;
};

} // battleship