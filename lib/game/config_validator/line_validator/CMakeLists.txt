set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(line_validator STATIC line_validator.cpp)

target_include_directories(line_validator PRIVATE
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(line_validator PRIVATE
  game_config
  config_validator
)