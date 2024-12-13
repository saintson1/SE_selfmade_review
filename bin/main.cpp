#include <iostream>

#include <game/game.hpp>

int main(int argc, char** argv) {
  std::cout << "saintson battleship" << std::endl;

  battleship::BattleShipGame game;

  game.MainEventLoop();

  return 0;
}