set(ENV{INCLUDE_DIRS} "$ENV{INCLUDE_DIRS};${CMAKE_CURRENT_SOURCE_DIR}")
set(ENV{INCLUDE_DIRS} "$ENV{INCLUDE_DIRS}")


set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(event event.cpp)

target_include_directories(event PRIVATE
  input_device
  ${INCLUDE_DIRS_LIST}
)