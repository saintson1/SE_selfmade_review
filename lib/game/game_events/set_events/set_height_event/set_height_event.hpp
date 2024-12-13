#ifndef _SET_HEIGHT_EVENT_HPP_
#define _SET_HEIGHT_EVENT_HPP_

#include <iostream>

#include <set_base.hpp>

#include <input_device/input_device.hpp>
#include <event/event.hpp>

namespace battleship {

class SetHeight : public SetBase {
 public:
  void Run() override;
  ExecuteStatus Execute(InputDevice& input, ExecuteAdditionalArgument& arg) override;
  ~SetHeight() override;
};

} // battleship

#endif // _SET_HEIGHT_EVENT_HPP_