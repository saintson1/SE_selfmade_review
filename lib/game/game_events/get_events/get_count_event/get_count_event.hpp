#ifndef _GET_COUNT_EVENT_HPP_
#define _GET_COUNT_EVENT_HPP_

#include <get_base.hpp>

#include <input_device/input_device.hpp>
#include <event/event.hpp>

namespace battleship {

class GetCount : public GetBase {
 public:
  void Run() override;
  ExecuteStatus Execute(InputDevice& input, ExecuteAdditionalArgument& arg) override;
  ~GetCount() override;
};

} // battleship

#endif // _SET_COUNT_EVENT_HPP_