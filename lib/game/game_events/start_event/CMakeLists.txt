set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(start_event start_event.cpp)

target_include_directories(start_event PUBLIC
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(start_event PUBLIC
  game_device
  event
)

target_link_libraries(start_event PUBLIC
  line_validator
)