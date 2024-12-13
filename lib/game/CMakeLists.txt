set(ENV{INCLUDE_DIRS} "$ENV{INCLUDE_DIRS};${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(game_config)
add_subdirectory(game_resource)
add_subdirectory(game_device)
add_subdirectory(game_strategies)
add_subdirectory(config_validator)
add_subdirectory(game_events)

set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(game STATIC game.cpp)

target_link_libraries(game PRIVATE
  event
  set_count_event
  set_height_event
  set_width_event
  set_strategy_event
  set_result_event
  get_count_event
  get_height_event
  get_width_event
  create_event
  load_event
  dump_event
  start_event
  stop_event
  shot_event
  finished_event
  win_event
  lose_event
)

target_link_libraries(game PRIVATE
  game_device
  command_device
  game_config
  config_strategy
  shot_strategy
  order_shot_strategy
)

target_include_directories(game PRIVATE
  ${INCLUDE_DIRS_LIST}
)