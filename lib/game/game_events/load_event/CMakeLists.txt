set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(load_event load_event.cpp)

target_include_directories(load_event PUBLIC
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(load_event PUBLIC
  game_device
  input_device
  event
)