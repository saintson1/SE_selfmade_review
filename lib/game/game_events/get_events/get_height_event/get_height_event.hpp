#ifndef _GET_HEIGHT_EVENT_HPP_
#define _GET_HEIGHT_EVENT_HPP_

#include <iostream>

#include <get_base.hpp>

#include <input_device/input_device.hpp>
#include <event/event.hpp>

namespace battleship {

class GetHeight : public GetBase {
 public:
  void Run() override;
  ExecuteStatus Execute(InputDevice&, ExecuteAdditionalArgument& arg) override;
  ~GetHeight() override;
};

} // battleship

#endif // _GET_HEIGHT_EVENT_HPP_