#ifndef _CREATE_EVENT_HPP_
#define _CREATE_EVENT_HPP_

#include <iostream>

#include <event.hpp>
#include <event_device.hpp>
#include <input_device/input_device.hpp>

namespace battleship {

class Create : public EventBase {
 public:
  Create()  = default;
  void Run() override;
  ExecuteStatus Execute(InputDevice& input, ExecuteAdditionalArgument& arg) override;
  ~Create() override;
};

template class MakeEvent<Create>;
} // battleship

#endif // _CREATE_EVENT_HPP_