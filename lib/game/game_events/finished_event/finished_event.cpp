#include "finished_event.hpp"

#include <iostream>
#include <memory>

#include <game_device/game_device.hpp>
#include <event.hpp>

namespace battleship {

Finished::~Finished() {  };

void Finished::Run() {
  if (is_finished) {
    std::cout << "yes" << std::endl;
  } else {
    std::cout << "no" << std::endl;
  }
};

ExecuteStatus Finished::Execute(InputDevice&, ExecuteAdditionalArgument& arg) {
  GameDevice& game_device = dynamic_cast<GameDevice&>(arg);

  if (game_device.GetStatus() != GameDevice::Status::IN_PROCESS) {
    is_finished = true;
  } else {
    is_finished = false;
  }

  Run();
  return ExecuteStatus::CORRECT;
};

} // battleship