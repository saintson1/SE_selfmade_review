#include "input_device.hpp"

#include <istream>
#include <iostream>
#include <memory>

namespace battleship {

InputDevice::InputDevice() :
  input_ptr_(&std::cin, [](std::istream*){}) {  };

InputDevice::InputDevice(std::istream& input_stream) :
  input_ptr_(&input_stream, [](std::istream*){}){  };

} // battleship