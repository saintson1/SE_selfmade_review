#include "ping_event.hpp"

#include <iostream>

namespace battleship {

Ping::~Ping() {  };

void Ping::Run() {
  std::cout << "pong" << std::endl;
};

} // battleship