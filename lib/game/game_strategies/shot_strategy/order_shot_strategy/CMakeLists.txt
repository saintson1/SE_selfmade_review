set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(order_shot_strategy STATIC order_shot_strategy.cpp)

target_include_directories(order_shot_strategy PRIVATE ${INCLUDE_DIRS_LIST})

target_link_libraries(order_shot_strategy PRIVATE 
  game_config
  game_device
  shot_strategy
)