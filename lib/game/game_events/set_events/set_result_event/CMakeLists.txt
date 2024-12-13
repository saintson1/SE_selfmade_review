set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(set_result_event STATIC set_result_event.cpp)

target_include_directories(set_result_event PRIVATE
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(set_result_event PRIVATE
  game_device
  input_device
  event
)