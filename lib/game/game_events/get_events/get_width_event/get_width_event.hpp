#ifndef _GET_WIDTH_EVENT_HPP_
#define _GET_WIDTH_EVENT_HPP_

#include <iostream>

#include <get_base.hpp>

#include <input_device/input_device.hpp>
#include <event/event.hpp>

namespace battleship {

class GetWidth : public GetBase {
 public:
  void Run() override;
  ExecuteStatus Execute(InputDevice&, ExecuteAdditionalArgument& arg) override;
  ~GetWidth() override;
};

} // battleship

#endif // _GET_WIDTH_EVENT_HPP_