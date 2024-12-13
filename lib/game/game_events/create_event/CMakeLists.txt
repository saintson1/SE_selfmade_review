set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(create_event create_event.cpp)

target_include_directories(create_event PUBLIC
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(create_event PUBLIC
  input_device
  event
)