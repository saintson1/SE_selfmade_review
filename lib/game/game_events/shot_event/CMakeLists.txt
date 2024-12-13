set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(shot_event shot_event.cpp)

target_include_directories(shot_event PUBLIC
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(shot_event PUBLIC
  input_device
  game_device
  event
)