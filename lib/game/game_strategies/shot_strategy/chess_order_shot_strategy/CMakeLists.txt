set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(chess_order_shot_strategy STATIC chess_order_shot_strategy.cpp)

target_include_directories(chess_order_shot_strategy PRIVATE ${INCLUDE_DIRS_LIST})

target_link_libraries(chess_order_shot_strategy PRIVATE
  game_config
  game_device
  shot_strategy
)