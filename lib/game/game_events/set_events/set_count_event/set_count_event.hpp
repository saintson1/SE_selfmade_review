#ifndef _SET_COUNT_EVENT_HPP_
#define _SET_COUNT_EVENT_HPP_

#include <set_base.hpp>

#include <input_device/input_device.hpp>
#include <event/event.hpp>

namespace battleship {

class SetCount : public SetBase {
 public:
  void Run() override;
  ExecuteStatus Execute(InputDevice& input, ExecuteAdditionalArgument& arg) override;
  ~SetCount() override;
};

} // battleship

#endif // _SET_COUNT_EVENT_HPP_