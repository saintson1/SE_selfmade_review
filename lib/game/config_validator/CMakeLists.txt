set(ENV{INCLUDE_DIRS} "$ENV{INCLUDE_DIRS};${CMAKE_CURRENT_SOURCE_DIR}")

set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(config_validator STATIC config_validator.cpp)

target_include_directories(config_validator PRIVATE
  ${INCLUDE_DIRS_LIST}
  game_config
)

add_subdirectory(line_validator)