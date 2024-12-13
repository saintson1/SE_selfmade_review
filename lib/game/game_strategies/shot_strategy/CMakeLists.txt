set(ENV{INCLUDE_DIRS} "$ENV{INCLUDE_DIRS};${CMAKE_CURRENT_SOURCE_DIR}")

set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(shot_strategy STATIC shot_strategy.cpp)

target_include_directories(shot_strategy PRIVATE ${INCLUDE_DIRS_LIST})

target_link_libraries(shot_strategy PRIVATE 
  game_config
  game_device
)

add_subdirectory(order_shot_strategy)
add_subdirectory(chess_order_shot_strategy)
add_subdirectory(circle_shot_strategy)