#include "set_width_event.hpp"

#include <iostream>
#include <sstream>
#include <string>

#include <event/event.hpp>
#include <game_device.hpp>

namespace battleship {

SetWidth::~SetWidth() {  };

void SetWidth::Run() {  };

ExecuteStatus SetWidth::Execute(InputDevice& input, ExecuteAdditionalArgument& arg) {
  std::string input_str;
  GameConfig::FieldSize width_buff;

  GameDevice& game_device = dynamic_cast<GameDevice&>(arg);

  if (game_device.GetState() != GameDevice::State::PREPARATION)
    return ExecuteStatus::EXECUTE_FAIL;

  input >> input_str;

  std::stringstream buff_stream(input_str);
  buff_stream >> width_buff;

  if (input.IsFail()) {
    std::cout << "failed" << std::endl;
    return ExecuteStatus::CORRECT;
  }
  if (buff_stream.fail()) {
    std::cout << "failed" << std::endl;
    return ExecuteStatus::CORRECT;
  }
  if (width_buff == 0) {
    std::cout << "failed" << std::endl;
    return ExecuteStatus::CORRECT;
  }

  game_device.GetConfig().field_w_ = width_buff;

  std::cout << "ok" << std::endl;
  return ExecuteStatus::CORRECT;
};

} // battleship