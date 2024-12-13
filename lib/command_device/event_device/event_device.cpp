#include "event_device.hpp"
#include "event/event.hpp"

#include <input_device/input_device.hpp>

namespace battleship {

EventDevice::EventDevice() : event_(nullptr) {  };

EventDevice::EventDevice(const std::shared_ptr<EventBase>& event) : event_(event) {  };

EventDevice::EventDevice(std::shared_ptr<EventBase>&& event) : event_(std::move(event)) {  };

EventDevice::EventDevice(EventBase* event) : event_(event) {  };

EventDevice::EventDevice(const EventDevice& value) : event_(value.event_) {  };

EventDevice& EventDevice::operator=(const EventDevice& value) {
  if (this == &value)
    return *this;

  event_ = value.event_;
  return *this;
};

EventDevice::EventDevice(EventDevice&& value) : event_(std::move(value.event_)) {  };

EventDevice& EventDevice::operator=(EventDevice&& value) {
  if (this == &value)
    return *this;

  event_ = std::move(value.event_);
  value.event_.reset();
  return *this;
};

ExecuteStatus EventDevice::Execute(ExecuteAdditionalArgument& arg) {
  return event_->Execute(arg);
};

ExecuteStatus EventDevice::Execute() {
  return event_->Execute();
};

ExecuteStatus EventDevice::Execute(InputDevice& input) {
  return event_->Execute(input);
};

ExecuteStatus EventDevice::Execute(InputDevice& input, ExecuteAdditionalArgument& arg) {
  return event_->Execute(input, arg);
};

MakeEventBase::~MakeEventBase() {  };

} // battleship