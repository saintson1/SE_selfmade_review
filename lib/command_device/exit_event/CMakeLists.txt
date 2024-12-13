set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(exit_event exit_event.cpp)

target_include_directories(exit_event PUBLIC
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(exit_event PUBLIC
  input_device
  event
)