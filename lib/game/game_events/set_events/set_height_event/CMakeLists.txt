set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(set_height_event STATIC set_height_event.cpp)

target_include_directories(set_height_event PRIVATE
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(set_height_event PRIVATE
  game_device
  event
)