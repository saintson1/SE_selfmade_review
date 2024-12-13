#include "set_strategy_event.hpp"

#include <iostream>
#include <string>

#include <event/event.hpp>
#include <game_device.hpp>

#include <order_shot_strategy/order_shot_strategy.hpp>
#include <chess_order_shot_strategy/chess_order_shot_strategy.hpp>

namespace battleship {

SetStrategy::~SetStrategy() {  };

void SetStrategy::Run() { 
  std::cout << "ok" << std::endl;
};

ExecuteStatus SetStrategy::Execute(InputDevice& input, ExecuteAdditionalArgument& arg) {
  std::string input_str;

  GameDevice& game_device = dynamic_cast<GameDevice&>(arg);

  input >> input_str;

  if (input.IsFail()) {
    std::cout << "failed" << std::endl;
    return ExecuteStatus::CORRECT;
  }

  if (input_str == "ordered") {
    game_device.SetShotStrategy<OrderShotStrategy>();
  } else if (input_str == "custom") {
    game_device.SetShotStrategy<ChessOrderShotStrategy>();
  } else {
    return ExecuteStatus::INVALID_INPUT;
  }

  Run();
  return ExecuteStatus::CORRECT;
};

} // battleship