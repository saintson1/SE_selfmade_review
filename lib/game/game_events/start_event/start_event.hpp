#ifndef _START_EVENT_HPP_
#define _START_EVENT_HPP_

#include <iostream>

#include <input_device/input_device.hpp>
#include <event_device.hpp>
#include <event/event.hpp>

namespace battleship {

class Start : public EventBase {
 public:
  Start()  = default;
  void Run() override;
  ExecuteStatus Execute(InputDevice&, ExecuteAdditionalArgument& arg) override;
  ~Start() override;
 private:
  bool is_done = false;
};

template class MakeEvent<Start>;

} // battleship

#endif // _START_EVENT_HPP_