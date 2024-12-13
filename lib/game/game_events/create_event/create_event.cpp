#include "create_event.hpp"

#include <iostream>
#include <string>

#include <event.hpp>
#include <game_device/game_device.hpp>
#include <config_strategy/config_strategy.hpp>

namespace battleship {

Create::~Create() {  };

void Create::Run() {
  std::cout << "ok" << std::endl;
};

ExecuteStatus Create::Execute(InputDevice& input, ExecuteAdditionalArgument& arg) {
  std::string role_buff;

  GameDevice& game_device = dynamic_cast<GameDevice&>(arg);

  if (game_device.GetState() != GameDevice::State::PREPARATION)
    return ExecuteStatus::EXECUTE_FAIL;

  input >> role_buff;

  if (input.IsFail()) {
    return ExecuteStatus::INVALID_INPUT;
  }

  Run();

  if (role_buff == "master") {
    game_device.SetRole(GameDevice::Role::MASTER);
    game_device.Configurate<ConfigStrategyClassic>();
    return ExecuteStatus::CORRECT;
  } else if (role_buff == "slave") {
    game_device.SetRole(GameDevice::Role::SLAVE);
    return ExecuteStatus::CORRECT;
  } else {
    return ExecuteStatus::EXECUTE_FAIL;
  }

  return ExecuteStatus::CORRECT;
};

} // battleship