#ifndef _FINISHED_EVENT_HPP_
#define _FINISHED_EVENT_HPP_

#include <iostream>

#include <input_device/input_device.hpp>
#include <event_device.hpp>
#include <event/event.hpp>

namespace battleship {

class Finished : public EventBase {
 public:
  Finished()  = default;
  void Run() override;
  ExecuteStatus Execute(InputDevice&, ExecuteAdditionalArgument& arg) override;
  ~Finished() override;
 private:
  bool is_finished = false;
};

template class MakeEvent<Finished>;

} // battleship

#endif // _FINISHED_EVENT_HPP_