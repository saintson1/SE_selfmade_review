#include "event.hpp"

#include <input_device/input_device.hpp>

namespace battleship {

ExecuteAdditionalArgument::~ExecuteAdditionalArgument() {  };

EventBase::~EventBase() {  };

ExecuteStatus EventBase::Execute(InputDevice&, ExecuteAdditionalArgument&) {
  return Execute();
};

ExecuteStatus EventBase::Execute(InputDevice&) {
  return Execute();
};

ExecuteStatus EventBase::Execute(ExecuteAdditionalArgument&) {
  return Execute();
};

ExecuteStatus EventBase::Execute() {
  Run();
  return status_;
};

void InvalidEvent::Run() {
  status_ = ExecuteStatus::INVALID_INPUT;
};

} // battleship