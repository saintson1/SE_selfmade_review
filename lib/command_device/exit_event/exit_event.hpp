#ifndef _EXIT_EVENT_HPP_
#define _EXIT_EVENT_HPP_

#include <event/event.hpp>

namespace battleship {

class Exit : public EventBase {
 public:
  Exit() = default;
  void Run() override;
  ~Exit() override;
};

} // battleship

#endif // _EXIT_EVENT_HPP_