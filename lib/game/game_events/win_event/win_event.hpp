#ifndef _WIN_EVENT_HPP_
#define _WIN_EVENT_HPP_

#include <iostream>

#include <input_device/input_device.hpp>
#include <event_device.hpp>
#include <event/event.hpp>

namespace battleship {

class Win : public EventBase {
 public:
  Win()  = default;
  void Run() override;
  ExecuteStatus Execute(InputDevice&, ExecuteAdditionalArgument& arg) override;
  ~Win() override;
 private:
  bool is_win = false;
};

template class MakeEvent<Win>;

} // battleship

#endif // _WIN_EVENT_HPP_