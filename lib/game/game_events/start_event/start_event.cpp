#include "start_event.hpp"

#include <iostream>
#include <memory>

#include <game_device/game_device.hpp>
#include <event.hpp>

#include <line_validator/line_validator.hpp>

#include <config_strategy/config_strategy.hpp>

namespace battleship {

Start::~Start() {  };

void Start::Run() {
  if (is_done) {
    std::cout << "ok" << std::endl;
  } else {
    std::cout << "fail" << std::endl;
  }
};

ExecuteStatus Start::Execute(InputDevice&, ExecuteAdditionalArgument& arg) {
  GameDevice& game_device = dynamic_cast<GameDevice&>(arg);

  if (game_device.GetState() != GameDevice::State::PREPARATION) {
    is_done = true;
    Run();
    return ExecuteStatus::EXECUTE_FAIL;
  }


  if (game_device.GetRole() == GameDevice::Role::MASTER) {
    is_done = true;
  } else if (game_device.GetRole() == GameDevice::Role::SLAVE) {
    is_done = game_device.Configurate({std::make_shared<LineValidator>(game_device.GetConfig())});
  } else {
    is_done = false;
    return ExecuteStatus::EXECUTE_FAIL;
  }

  Run();
  return ExecuteStatus::CORRECT;
};

} // battleship