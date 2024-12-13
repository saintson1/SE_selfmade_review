#include "game.hpp"

#include <utility>
#include <string>
#include <iostream>

#include <game_device/game_device.hpp>
#include <input_device/input_device.hpp>
#include <command_device/command_device.hpp>

#include <game_events/game_events.hpp>

namespace battleship {

BattleShipGame::BattleShipGame() :
  BattleShipGame(Command{}) {  };

BattleShipGame::BattleShipGame(Command&& cmd) :
  cmd_(std::move(cmd)) {
    cmd_.AddCommands(
      std::pair<std::string, Create>{"create",{}},
      std::pair<std::string, GetBase>{"get",{}},
      std::pair<std::string, SetBase>{"set",{}},
      std::pair<std::string, Load>{"load",{}},
      std::pair<std::string, Dump>{"dump",{}},
      std::pair<std::string, Start>{"start",{}},
      std::pair<std::string, Win>{"win",{}},
      std::pair<std::string, Lose>{"lose",{}},
      std::pair<std::string, Finished>{"finished",{}},
      std::pair<std::string, Shot>{"shot",{}},
      std::pair<std::string, Stop>{"stop",{}}
    );
};

BattleShipGame::BattleShipGame(BattleShipGame&& value) :
  cmd_(std::move(value.cmd_)) {  };

BattleShipGame& BattleShipGame::operator=(BattleShipGame&& value) {
  if (this == &value)
    return *this;

  cmd_ = std::move(value.cmd_);
  return *this;
};

void BattleShipGame::MainEventLoop() {
  InputDevice in;
  MainEventLoop(in);
};

void BattleShipGame::MainEventLoop(InputDevice& input_device) {
  GameDevice game;

  while(true) {
    auto res = cmd_.GetCommand();
    if (input_device.IsFail()) {
      std::cout << "end of stream" << std::endl;
      break;
    }

    auto exe_res = res.Execute(input_device, game);
    if (exe_res == battleship::ExecuteStatus::EXIT)
      break;
    else if (exe_res == battleship::ExecuteStatus::INVALID_INPUT)
      std::cout << "invalid input" << std::endl;
  }
};

} // battleship