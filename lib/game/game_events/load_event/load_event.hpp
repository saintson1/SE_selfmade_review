#ifndef _LOAD_EVENT_HPP_
#define _LOAD_EVENT_HPP_

#include <iostream>

#include <input_device/input_device.hpp>
#include <event/event.hpp>
#include <event_device.hpp>

namespace battleship {

class Load : public EventBase {
 public:
  Load()  = default;
  void Run() override;
  ExecuteStatus Execute(InputDevice& input, ExecuteAdditionalArgument& arg) override;
  ~Load() override;
};

template class MakeEvent<Load>;

} // battleship

#endif // _LOAD_EVENT_HPP_