set(ENV{INCLUDE_DIRS} "$ENV{INCLUDE_DIRS};${CMAKE_CURRENT_SOURCE_DIR}")

set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(game_device STATIC game_device.cpp)

target_include_directories(game_device PRIVATE
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(game_device PRIVATE
  unique_name_generator
  game_config
  ship
  ship_coordinates
)