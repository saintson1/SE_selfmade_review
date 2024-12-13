#ifndef _PING_EVENT_HPP_
#define _PING_EVENT_HPP_

#include <event/event.hpp>

namespace battleship {

class Ping : public EventBase {
 public:
  Ping() = default;
  void Run() override;
  ~Ping() override;
};

} // battleship

#endif // _PING_EVENT_HPP_