#ifndef _GET_BASE_HPP_
#define _GET_BASE_HPP_

#include <event/event.hpp>

namespace battleship {

class GetBase : public EventBase {
 public:
  ~GetBase() override {  };
  void Run() override {  };
};

} // battleship

#endif // _GET_BASE_HPP_