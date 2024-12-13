#ifndef _SHOT_EVENT_HPP_
#define _SHOT_EVENT_HPP_

#include <iostream>

#include <game_resource/shot/shot.hpp>
#include <game_device/game_device.hpp>
#include <input_device/input_device.hpp>
#include <event_device.hpp>
#include <event/event.hpp>

namespace battleship {

class Shot : public EventBase {
 public:
  Shot()  = default;
  void Run() override;
  ExecuteStatus Execute(InputDevice& input, ExecuteAdditionalArgument& arg) override;
  ~Shot() override;
 private:
  ShotState result_ = ShotState::MISS;
};

template class MakeEvent<Shot>;

} // battleship

#endif // _SHOT_EVENT_HPP_