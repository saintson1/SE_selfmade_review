set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(stop_event stop_event.cpp)

target_include_directories(stop_event PUBLIC
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(stop_event PUBLIC
  game_device
  event
)