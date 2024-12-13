#ifndef _DUMP_EVENT_HPP_
#define _DUMP_EVENT_HPP_

#include <iostream>

#include <input_device/input_device.hpp>
#include <event/event.hpp>
#include <event_device.hpp>

namespace battleship {

class Dump : public EventBase {
 public:
  Dump()  = default;
  void Run() override;
  ExecuteStatus Execute(InputDevice& input, ExecuteAdditionalArgument& arg) override;
  ~Dump() override;
};

template class MakeEvent<Dump>;

} // battleship

#endif // _DUMP_EVENT_HPP_