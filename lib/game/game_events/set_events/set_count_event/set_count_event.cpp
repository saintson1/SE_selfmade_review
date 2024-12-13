#include "set_count_event.hpp"

#include <event/event.hpp>
#include <game_device.hpp>

#include <iostream>
#include <sstream>
#include <vector>

namespace battleship {

SetCount::~SetCount() {  };

void SetCount::Run() {  };

ExecuteStatus SetCount::Execute(InputDevice& input, ExecuteAdditionalArgument& arg) {
  GameConfig::CountType count;
  std::string input_str;
  std::vector<GameConfig::CountType>::size_type type;

  GameDevice& game_device = dynamic_cast<GameDevice&>(arg);

  if (game_device.GetState() != GameDevice::State::PREPARATION)
    return ExecuteStatus::EXECUTE_FAIL;

  input >> input_str;

  std::stringstream buff_stream(input_str);
  buff_stream >> type;

  if (input.IsFail()) {
    std::cout << "failed" << std::endl;
    return ExecuteStatus::CORRECT;
  }
  if (buff_stream.fail()) {
    std::cout << "failed" << std::endl;
    return ExecuteStatus::CORRECT;
  }
  if (!(0 < type && type < 5)) {
    std::cout << "failed" << std::endl;
    return ExecuteStatus::CORRECT;
  }
  input_str.clear();
  buff_stream.clear();

  input >> input_str;
  buff_stream.str(input_str);
  buff_stream >> count;

  if (input.IsFail()) {
    std::cout << "failed" << std::endl;
    return ExecuteStatus::CORRECT;
  }
  if (buff_stream.fail()) {
    std::cout << "failed" << std::endl;
    return ExecuteStatus::CORRECT;
  }
  if (count == 0) {
    std::cout << "failed" << std::endl;
    return ExecuteStatus::CORRECT;
  }

  game_device.GetConfig().ship_counts_[type - 1] = count;

  std::cout << "ok" << std::endl;
  return ExecuteStatus::CORRECT;
};

} // battleship