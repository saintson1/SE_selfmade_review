#ifndef _GET_EVENTS_HPP_
#define _GET_EVENTS_HPP_

#include <algorithm>
#include <memory>
#include <string>
#include <event_device.hpp>

#include "event.hpp"

#include "get_base.hpp"

#include "get_count_event/get_count_event.hpp"
#include "get_height_event/get_height_event.hpp"
#include "get_width_event/get_width_event.hpp"

namespace battleship {

namespace {

std::shared_ptr<EventBase> GetEventsCreate(const std::string& add_input) {
    if (add_input == "width") {
      return std::shared_ptr<GetWidth>{new GetWidth{}};
    } else if (add_input == "height") {
      return std::shared_ptr<GetHeight>{new GetHeight{}};
    } else if (add_input == "count") {
      return std::shared_ptr<GetCount>{new GetCount{}};
    } else {
      return std::shared_ptr<InvalidEvent>{new InvalidEvent{}};
    }
};

} // namespace

template<>
class MakeEvent<GetBase> : public MakeEventBase {
 public:
  MakeEvent() = default;
  ~MakeEvent() = default;
 public:
  EventDevice operator()(InputDevice& input) override {
    std::string in_buff;
    input >> in_buff;
    return GetEventsCreate(in_buff);
  };
};

} // battleship

#endif // _GET_EVENTS_HPP_