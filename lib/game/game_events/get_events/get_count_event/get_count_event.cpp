#include "get_count_event.hpp"

#include <event/event.hpp>
#include <game_device.hpp>

#include <iostream>
#include <sstream>
#include <vector>

namespace battleship {

GetCount::~GetCount() {  };

void GetCount::Run() {  };

ExecuteStatus GetCount::Execute(InputDevice& input, ExecuteAdditionalArgument& arg) {
  std::string input_str;
  std::vector<GameConfig::CountType>::size_type type;

  GameDevice& game_device = dynamic_cast<GameDevice&>(arg);

if (game_device.GetRole() != GameDevice::Role::MASTER)    return ExecuteStatus::EXECUTE_FAIL;

  input >> input_str;

  std::stringstream buff_stream(input_str);
  buff_stream >> type;

  if (input.IsFail()) {
    return ExecuteStatus::EXECUTE_FAIL;
  }
  if (buff_stream.fail()) {
    return ExecuteStatus::EXECUTE_FAIL;
  }

  decltype(auto) cfg_ships = game_device.GetConfig().ship_counts_;

  if (type > cfg_ships.size())
    return ExecuteStatus::EXECUTE_FAIL;

  std::cout << cfg_ships[type - 1] << std::endl;
  return ExecuteStatus::CORRECT;
};

} // battleship