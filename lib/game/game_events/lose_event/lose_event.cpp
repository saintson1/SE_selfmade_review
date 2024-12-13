#include "lose_event.hpp"

#include <iostream>
#include <memory>

#include <game_device/game_device.hpp>
#include <event.hpp>

namespace battleship {

Lose::~Lose() {  };

void Lose::Run() {
  if (is_lose) {
    std::cout << "yes" << std::endl;
  } else {
    std::cout << "no" << std::endl;
  }
};

ExecuteStatus Lose::Execute(InputDevice&, ExecuteAdditionalArgument& arg) {
  GameDevice& game_device = dynamic_cast<GameDevice&>(arg);

  if (game_device.GetStatus() == GameDevice::Status::OPONENT_WIN) {
    is_lose = true;
  } else {
    is_lose = false;
  }

  Run();
  return ExecuteStatus::CORRECT;
};

} // battleship