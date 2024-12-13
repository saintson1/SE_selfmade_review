#include "command_device.hpp"

#include <string>
#include <string_view>
#include <memory>
#include <unordered_map>

#include <input_device/input_device.hpp>
#include "def_event.hpp"
#include "event_device/event_device.hpp"

namespace battleship {

Command::Command() : Command(InputDevice{}) { 
};

Command::Command(const InputDevice& input) : 
  input_(input), make_event_cont_({
    {"ping", std::make_shared<MakeEvent<Ping>>()},
    {"exit", std::make_shared<MakeEvent<Exit>>()}
    }) {  };

Command::Command(InputDevice&& input) :
  input_(std::move(input)) , make_event_cont_({
    {"ping", std::make_shared<MakeEvent<Ping>>()},
    {"exit", std::make_shared<MakeEvent<Exit>>()}
    }) {  };

Command::Command(Command&& value) :
  input_(std::move(value.input_)), make_event_cont_(value.make_event_cont_) {  };

Command& Command::operator=(Command&& value) {
  if (this == &value)
    return *this;
  input_ = std::move(value.input_);
  make_event_cont_ = std::move(value.make_event_cont_);
  return *this;
};

std::string Command::GetValue() {
  std::string input_buff;
  input_ >> input_buff;
  return input_buff;
};

EventDevice Command::GetCommand() {
  return CreateEvent(GetValue());
};

EventDevice Command::CreateEvent(std::string_view value) {
  return make_event_cont_.find({value.begin(), value.end()}) != make_event_cont_.end() ?
      (*(make_event_cont_.find({value.begin(), value.end()})->second))(input_) :
        EventDevice(new InvalidEvent{});
};

EventDevice Command::CreateEvent(std::string value) {
  return CreateEvent(std::string_view{value.begin(), value.end()});
};

} // battleship