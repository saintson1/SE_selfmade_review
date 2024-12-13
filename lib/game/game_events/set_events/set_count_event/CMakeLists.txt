set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(set_count_event STATIC set_count_event.cpp)

target_include_directories(set_count_event PUBLIC
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(set_count_event PUBLIC
  game_device
  event
)