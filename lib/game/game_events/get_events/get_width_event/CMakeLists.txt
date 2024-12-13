set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(get_width_event STATIC get_width_event.cpp)

target_include_directories(get_width_event PRIVATE
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(get_width_event PRIVATE
  game_device
  event
)