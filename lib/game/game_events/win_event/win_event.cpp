#include "win_event.hpp"

#include <iostream>
#include <memory>

#include <game_device/game_device.hpp>
#include <event.hpp>

namespace battleship {

Win::~Win() {  };

void Win::Run() {
  if (is_win) {
    std::cout << "yes" << std::endl;
  } else {
    std::cout << "no" << std::endl;
  }
};

ExecuteStatus Win::Execute(InputDevice&, ExecuteAdditionalArgument& arg) {
  GameDevice& game_device = dynamic_cast<GameDevice&>(arg);

  if (game_device.GetStatus() == GameDevice::Status::BOT_WIN) {
    is_win = true;
  } else {
    is_win = false;
  }

  Run();
  return ExecuteStatus::CORRECT;
};

} // battleship