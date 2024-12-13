set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(input_device STATIC input_device.cpp)

target_include_directories(input_device PRIVATE
  ${INCLUDE_DIRS_LIST}
)