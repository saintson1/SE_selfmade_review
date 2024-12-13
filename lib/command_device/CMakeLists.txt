add_subdirectory(event_device)

add_subdirectory(exit_event)
add_subdirectory(ping_event)

set(ENV{INCLUDE_DIRS} "$ENV{INCLUDE_DIRS}")

set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(command_device STATIC command_device.cpp)

target_include_directories(command_device PRIVATE
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(command_device PRIVATE
  create_event
  input_device
  event_device
  event
  ping_event
  exit_event
)