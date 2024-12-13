#include "shot_event.hpp"

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include <game_device/game_device.hpp>
#include <input_device/input_device.hpp>
#include <game_resource/shot/shot.hpp>
#include <event.hpp>

namespace battleship {

Shot::~Shot() {  };

void Shot::Run() {
  if (result_ == ShotState::MISS) {
    std::cout << "miss" << std::endl;
  } else if (result_ == ShotState::HIT) {
    std::cout << "hit" << std::endl;
  } else if (result_ == ShotState::KILL) {
    std::cout << "kill" << std::endl;
  }
};

ExecuteStatus Shot::Execute(InputDevice& input, ExecuteAdditionalArgument& arg) {
  GameDevice& game_device = dynamic_cast<GameDevice&>(arg);

  if (game_device.GetState() == GameDevice::State::PREPARATION)
    return ExecuteStatus::EXECUTE_FAIL;

  if (game_device.GetState() == GameDevice::State::BOT_MOVE) {
    auto [x, y] = game_device.GiveShot();
    std::cout << std::to_string(x) << " " << std::to_string(y) << std::endl;
    // game_device.
  } else if (game_device.GetState() == GameDevice::State::OPONENT_MOVE) {
    uint64_t x_shot_coord, y_shot_coord;

    std::string input_str;
    input >> input_str;

    std::stringstream buff_stream(input_str);

    buff_stream >> x_shot_coord;
    if (input.IsFail()) {
      return ExecuteStatus::EXECUTE_FAIL;
    }
    if (buff_stream.fail()) {
      return ExecuteStatus::EXECUTE_FAIL;
    }
    input_str.clear();
    buff_stream.clear();

    input >> input_str;
    buff_stream.str(input_str);

    buff_stream >> y_shot_coord;
    if (input.IsFail()) {
      return ExecuteStatus::EXECUTE_FAIL;
    }
    if (buff_stream.fail()) {
      return ExecuteStatus::EXECUTE_FAIL;
    }

    result_ = game_device.TakeShot({x_shot_coord, y_shot_coord});
    Run();
  }

  return ExecuteStatus::CORRECT;
};

} // battleship