#include "load_event.hpp"

#include <iostream>

#include <game_device/game_device.hpp>
#include <event.hpp>


namespace battleship {

Load::~Load() {  };

void Load::Run() {
  std::cout << "ok" << std::endl;
};

ExecuteStatus Load::Execute(InputDevice& input, ExecuteAdditionalArgument& arg) {
  std::string path;

  GameDevice& game_device = dynamic_cast<GameDevice&>(arg);

  if (game_device.GetState() != GameDevice::State::PREPARATION)
    return ExecuteStatus::EXECUTE_FAIL;

  input >> path;

  if (input.IsFail()) {
    return ExecuteStatus::INVALID_INPUT;
  }

  Run();

  if (game_device.Load(path)) {
    return ExecuteStatus::CORRECT;
  } else {
    return ExecuteStatus::EXECUTE_FAIL;
  }
};

} // battleship