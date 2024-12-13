#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <event/event.hpp>

#include <input_device/input_device.hpp>
#include <command_device/command_device.hpp>

namespace battleship {

class BattleShipGame {
 public:
  BattleShipGame();
  BattleShipGame(Command&& cmd);
  BattleShipGame(const BattleShipGame& value) = delete;
  BattleShipGame(BattleShipGame&& value);
  BattleShipGame& operator=(BattleShipGame&& value);
  ~BattleShipGame() = default;

 public:
  void MainEventLoop(InputDevice& input_device);
  void MainEventLoop();
 private:
  battleship::Command cmd_;
};

} // battleship

#endif // _GAME_HPP_