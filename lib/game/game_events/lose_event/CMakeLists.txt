set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(lose_event lose_event.cpp)

target_include_directories(lose_event PUBLIC
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(lose_event PUBLIC
  game_device
  event
)