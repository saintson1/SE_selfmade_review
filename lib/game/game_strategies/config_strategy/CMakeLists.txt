set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(config_strategy STATIC config_strategy.cpp)

target_include_directories(config_strategy PRIVATE ${INCLUDE_DIRS_LIST})

target_link_libraries(config_strategy PRIVATE
  unique_name_generator
  ship_coordinates
  ship
  game_config
)