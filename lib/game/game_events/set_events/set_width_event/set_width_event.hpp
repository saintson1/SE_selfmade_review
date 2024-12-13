#ifndef _SET_WIDTH_EVENT_HPP_
#define _SET_WIDTH_EVENT_HPP_

#include <iostream>

#include <set_base.hpp>

#include <input_device/input_device.hpp>
#include <event/event.hpp>

namespace battleship {

class SetWidth : public SetBase {
 public:
  void Run() override;
  ExecuteStatus Execute(InputDevice& input, ExecuteAdditionalArgument& arg) override;
  ~SetWidth() override;
};

} // battleship

#endif // _SET_WIDTH_EVENT_HPP_