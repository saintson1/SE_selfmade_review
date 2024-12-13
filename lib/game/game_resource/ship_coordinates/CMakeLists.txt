set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(ship_coordinates STATIC ship_coordinates.cpp)

target_include_directories(ship_coordinates PRIVATE
  ${INCLUDE_DIRS_LIST}
)

add_executable(ship_coordinates_test ship_coordinates_test.cpp)

target_include_directories(ship_coordinates_test  PRIVATE
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(ship_coordinates_test PRIVATE
  ship
  ship_coordinates
)