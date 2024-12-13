#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include <input_device/input_device.hpp>

namespace battleship {

class ExecuteAdditionalArgument {
 public:
  virtual ~ExecuteAdditionalArgument();
};

enum ExecuteStatus {
  CORRECT,
  EXIT,
  INVALID_INPUT,
  EXECUTE_FAIL,
};

class EventBase {
 public:
  EventBase() = default;
  virtual ~EventBase() = 0;

 public:
  virtual ExecuteStatus Execute(InputDevice&, ExecuteAdditionalArgument&);
  virtual ExecuteStatus Execute(ExecuteAdditionalArgument&);
  virtual ExecuteStatus Execute(InputDevice&);
  virtual ExecuteStatus Execute();
  virtual void Run() = 0;
 protected:
  ExecuteStatus status_ = ExecuteStatus::CORRECT;
};

class InvalidEvent : public EventBase {
 public:
  InvalidEvent() = default;
  ~InvalidEvent() override = default;
 public:
  void Run() override;
};

} // battleship

#endif // _EVENT_HPP_