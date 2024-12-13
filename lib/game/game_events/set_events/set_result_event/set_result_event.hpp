#ifndef _SET_RESULT_EVENT_HPP_
#define _SET_RESULT_EVENT_HPP_

#include <iostream>

#include <set_base.hpp>

#include <input_device/input_device.hpp>
#include <event/event.hpp>

namespace battleship {

class SetResult : public SetBase {
 public:
  void Run() override;
  ExecuteStatus Execute(InputDevice& input, ExecuteAdditionalArgument& arg) override;
  ~SetResult() override;
};

} // battleship

#endif // _SET_RESULT_EVENT_HPP_