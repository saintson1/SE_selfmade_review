set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(ping_event ping_event.cpp)

target_include_directories(ping_event PUBLIC
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(ping_event PUBLIC
  input_device
  event
)