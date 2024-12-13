set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(finished_event finished_event.cpp)

target_include_directories(finished_event PUBLIC
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(finished_event PUBLIC
  game_device
  event
)