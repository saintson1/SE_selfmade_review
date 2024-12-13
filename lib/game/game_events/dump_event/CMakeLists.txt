set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(dump_event dump_event.cpp)

target_include_directories(dump_event PUBLIC
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(dump_event PUBLIC
  input_device
  event
)