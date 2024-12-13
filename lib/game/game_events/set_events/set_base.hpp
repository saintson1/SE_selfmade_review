#ifndef _SET_BASE_HPP_
#define _SET_BASE_HPP_

#include <event/event.hpp>

namespace battleship {

class SetBase : public EventBase {
 public:
  ~SetBase() override {  };
  void Run() override {  };
};

} // battleship

#endif // _SET_BASE_HPP_