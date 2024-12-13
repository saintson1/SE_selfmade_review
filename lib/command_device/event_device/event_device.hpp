#ifndef _EVENT_DEVICE_HPP_
#define _EVENT_DEVICE_HPP_

#include "event/event.hpp"
#include <memory>

#include <event.hpp>
#include <input_device/input_device.hpp>

namespace battleship {

template<typename DerivedType, typename BaseType>
concept IsInheritor = std::is_base_of_v<BaseType, DerivedType>;

class EventDevice {
 public:
  EventDevice();
  EventDevice(const std::shared_ptr<EventBase>& event);
  EventDevice(std::shared_ptr<EventBase>&& event);
  EventDevice(EventBase* event);
  EventDevice(const EventDevice& value);
  EventDevice& operator=(const EventDevice& value);
  EventDevice(EventDevice&& value);
  EventDevice& operator=(EventDevice&& value);
  ~EventDevice() = default;
  ExecuteStatus Execute(InputDevice& input);
  ExecuteStatus Execute(InputDevice& input, ExecuteAdditionalArgument& arg);
  ExecuteStatus Execute(ExecuteAdditionalArgument& arg);
  ExecuteStatus Execute();
public:
  static EventDevice GetEmptyDevice();

 private:
  std::shared_ptr<EventBase> event_;
};

class MakeEventBase {
 public:
  virtual EventDevice operator()(InputDevice&) = 0;
  virtual ~MakeEventBase() = 0;
};

template<IsInheritor<EventBase> EventType>
class MakeEvent : public MakeEventBase {
 public:
  MakeEvent() = default;
 public:
  EventDevice operator()(InputDevice&) override {
    return EventDevice(std::shared_ptr<EventType>{new EventType{}});
  };

 public:
  ~MakeEvent() = default;
};

} //battleship

#endif // _EVENT_DEVICE_HPP_
