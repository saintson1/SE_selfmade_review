#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

#include <unordered_map>
#include <memory>
#include <type_traits>

#include "def_event.hpp"

#include "command_device/event_device/event_device.hpp"
#include "input_device/input_device.hpp"
#include "event_device/event_device.hpp"


namespace battleship {

class Command {
 public:
  Command();
  Command(const InputDevice& input);
  Command(InputDevice&& input);
  Command(const Command& value) = delete;
  Command(Command&& value);
  Command& operator=(Command&& value);
 public:
  template<IsInheritor<EventBase>... EventTypes>
  bool AddCommands(std::pair<std::string, EventTypes>... events);
 public:
  EventDevice GetCommand();
 private:
  std::string GetValue();

  EventDevice CreateEvent(std::string value);
  EventDevice CreateEvent(std::string_view value);
 private:
  std::unordered_map<std::string, std::shared_ptr<MakeEventBase>> make_event_cont_;
  InputDevice input_;
};

template<IsInheritor<EventBase>... EventTypes>
bool Command::AddCommands(std::pair<std::string, EventTypes>... events) {
  return (make_event_cont_.insert({events.first,
    std::make_shared<MakeEvent<EventTypes>>()}).second && ...);
};

} // battleship

#endif // _COMMAND_HPP_