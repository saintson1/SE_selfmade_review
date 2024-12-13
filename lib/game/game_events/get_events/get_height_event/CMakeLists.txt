set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(get_height_event STATIC get_height_event.cpp)

target_include_directories(get_height_event PRIVATE
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(get_height_event PRIVATE
  game_device
  event
)