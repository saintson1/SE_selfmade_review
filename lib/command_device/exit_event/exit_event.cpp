#include "exit_event.hpp"

namespace battleship {

Exit::~Exit() {  };

void Exit::Run() {
  status_ = ExecuteStatus::EXIT;
};

} // battleship