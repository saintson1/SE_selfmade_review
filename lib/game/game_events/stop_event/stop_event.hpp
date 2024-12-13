#ifndef _STOP_EVENT_HPP_
#define _STOP_EVENT_HPP_

#include <iostream>

#include <input_device/input_device.hpp>
#include <event_device.hpp>
#include <event/event.hpp>

namespace battleship {

class Stop : public EventBase {
 public:
  Stop()  = default;
  void Run() override;
  ExecuteStatus Execute(InputDevice&, ExecuteAdditionalArgument& arg) override;
  ~Stop() override;
};

template class MakeEvent<Stop>;

} // battleship

#endif // _STOP_EVENT_HPP_