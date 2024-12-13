set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(win_event win_event.cpp)

target_include_directories(win_event PUBLIC
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(win_event PUBLIC
  game_device
  event
)