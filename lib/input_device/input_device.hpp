#ifndef _INPUT_DEVICE_
#define _INPUT_DEVICE_

#include <memory>
#include <istream>

namespace battleship {

class InputDevice {
 public:
  InputDevice();

  template<typename DeleterType>
  InputDevice(std::istream& input_stream, DeleterType deleter);

  InputDevice(std::istream& input_stream);

  ~InputDevice() = default;

 public:
  template<typename DataType>
  InputDevice& operator>>(DataType& data);

  bool IsFail() { return input_ptr_->fail(); }

 private:
  std::shared_ptr<std::istream> input_ptr_;
};

template<typename DeleterType>
InputDevice::InputDevice(std::istream& input_stream, DeleterType deleter) :
  input_ptr_(&input_stream, deleter) {  };


template<typename DataType>
InputDevice& InputDevice::operator>>(DataType& data) {
  (*input_ptr_) >> data;
  return *this;
};

} // battleship

#endif // _INPUT_DEVICE_