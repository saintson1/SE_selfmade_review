#ifndef _LOSE_EVENT_HPP_
#define _LOSE_EVENT_HPP_

#include <iostream>

#include <input_device/input_device.hpp>
#include <event_device.hpp>
#include <event/event.hpp>

namespace battleship {

class Lose : public EventBase {
 public:
  Lose()  = default;
  void Run() override;
  ExecuteStatus Execute(InputDevice&, ExecuteAdditionalArgument& arg) override;
  ~Lose() override;
 private:
  bool is_lose = false;
};

template class MakeEvent<Lose>;

} // battleship

#endif // _LOSE_EVENT_HPP_