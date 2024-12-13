#include "set_height_event.hpp"

#include <iostream>
#include <sstream>
#include <string>

#include <event/event.hpp>
#include <game_device.hpp>

namespace battleship {

SetHeight::~SetHeight() {  };

void SetHeight::Run() {  };

ExecuteStatus SetHeight::Execute(InputDevice& input, ExecuteAdditionalArgument& arg) {
  GameConfig::FieldSize height_buff;
  std::string input_str;

  GameDevice& game_device = dynamic_cast<GameDevice&>(arg);

  if (game_device.GetState() != GameDevice::State::PREPARATION)
    return ExecuteStatus::EXECUTE_FAIL;

  input >> input_str;

  std::stringstream buff_stream(input_str);
  buff_stream >> height_buff;

  if (input.IsFail()) {
    std::cout << "failed" << std::endl;
    return ExecuteStatus::CORRECT;
  }
  if (buff_stream.fail()) {
    std::cout << "failed" << std::endl;
    return ExecuteStatus::CORRECT;
  }
  if (height_buff == 0) {
    std::cout << "failed" << std::endl;
    return ExecuteStatus::CORRECT;
  }

  game_device.GetConfig().field_h_ = height_buff;

  std::cout << "ok" << std::endl;
  return ExecuteStatus::CORRECT;
};

} // battleship