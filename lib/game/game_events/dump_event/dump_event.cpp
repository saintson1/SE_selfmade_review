#include "dump_event.hpp"

#include <iostream>

#include <game_device/game_device.hpp>
#include <event.hpp>


namespace battleship {

Dump::~Dump() {  };

void Dump::Run() {
  std::cout << "ok" << std::endl;
};

ExecuteStatus Dump::Execute(InputDevice& input, ExecuteAdditionalArgument& arg) {
  std::string path;

  GameDevice& game_device = dynamic_cast<GameDevice&>(arg);

  input >> path;

  if (input.IsFail()) {
    return ExecuteStatus::INVALID_INPUT;
  }

  Run();

  if (game_device.Dump<true>(path)) {
    return ExecuteStatus::CORRECT;
  } else {
    return ExecuteStatus::EXECUTE_FAIL;
  }
};

} // battleship