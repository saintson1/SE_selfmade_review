set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(ship STATIC ship.cpp)

target_include_directories(ship PRIVATE
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(ship PRIVATE
  ship_coordinates
)

add_executable(ship_test ship_test.cpp)

target_include_directories(ship_test PRIVATE
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(ship_test PRIVATE
  unique_name_generator
  ship
)