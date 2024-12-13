set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(set_strategy_event STATIC set_strategy_event.cpp)

target_include_directories(set_strategy_event PRIVATE
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(set_strategy_event PRIVATE
  game_device
  event
  order_shot_strategy
  chess_order_shot_strategy
)