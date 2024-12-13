#include "set_result_event.hpp"

#include <iostream>
#include <string>

#include <game_resource/shot/shot.hpp>
#include <event/event.hpp>
#include <game_device.hpp>
#include <input_device/input_device.hpp>

namespace battleship {

SetResult::~SetResult() {  };

void SetResult::Run() { 
  std::cout << "ok" << std::endl;
};

ExecuteStatus SetResult::Execute(InputDevice& input, ExecuteAdditionalArgument& arg) {
  std::string input_str;

  GameDevice& game_device = dynamic_cast<GameDevice&>(arg);

  if (game_device.GetState() == GameDevice::State::PREPARATION)
    return ExecuteStatus::EXECUTE_FAIL;

  input >> input_str;

  if (input.IsFail()) {
    std::cout << "failed" << std::endl;
    return ExecuteStatus::CORRECT;
  }

  if (input_str == "hit") {
    game_device.TakeShotResult(ShotState::HIT);
  } else if (input_str == "kill") {
    game_device.TakeShotResult(ShotState::KILL);
  } else if (input_str == "miss") {
    game_device.TakeShotResult(ShotState::MISS);
  } else {
    return ExecuteStatus::INVALID_INPUT;
  }

  Run();
  return ExecuteStatus::CORRECT;
};

} // battleship