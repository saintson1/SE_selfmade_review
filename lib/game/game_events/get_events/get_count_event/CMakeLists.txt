set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(get_count_event STATIC get_count_event.cpp)

target_include_directories(get_count_event PUBLIC
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(get_count_event PUBLIC
  game_device
  event
)