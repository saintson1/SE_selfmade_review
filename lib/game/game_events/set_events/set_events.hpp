#ifndef _SET_EVENTS_HPP_
#define _SET_EVENTS_HPP_

#include <algorithm>
#include <memory>
#include <string>
#include <event_device.hpp>

#include "event.hpp"

#include "set_base.hpp"

#include "set_count_event/set_count_event.hpp"
#include "set_height_event/set_height_event.hpp"
#include "set_result_event/set_result_event.hpp"
#include "set_strategy_event/set_strategy_event.hpp"
#include "set_width_event/set_width_event.hpp"

namespace battleship {

namespace {

std::shared_ptr<EventBase> SetEventsCreate(const std::string& add_input) {
    if (add_input == "width") {
      return std::shared_ptr<SetWidth>{new SetWidth{}};
    } else if (add_input == "height") {
      return std::shared_ptr<SetHeight>{new SetHeight{}};
    } else if (add_input == "count") {
      return std::shared_ptr<SetCount>{new SetCount{}};
    } else if (add_input == "strategy") {
      return std::shared_ptr<SetStrategy>{new SetStrategy{}};
    } else if (add_input == "result") {
      return std::shared_ptr<SetResult>{new SetResult{}};
    } else {
      return std::shared_ptr<InvalidEvent>{new InvalidEvent{}};
    }
};

} // namespace

template<>
class MakeEvent<SetBase> : public MakeEventBase {
 public:
  MakeEvent() = default;
  ~MakeEvent() = default;
 public:
  EventDevice operator()(InputDevice& input) override {
    std::string in_buff;
    input >> in_buff;
    return SetEventsCreate(in_buff);
  };
};

} // battleship

#endif // _SET_EVENTS_HPP_