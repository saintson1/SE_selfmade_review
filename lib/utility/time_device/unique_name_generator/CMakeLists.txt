set(ENV{INCLUDE_DIRS} "$ENV{INCLUDE_DIRS};${CMAKE_CURRENT_SOURCE_DIR}")

set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")

add_library(unique_name_generator STATIC unique_name_generator.cpp)

add_executable(unique_name_generator_test unique_name_generator_test.cpp)
target_link_libraries(unique_name_generator_test PRIVATE 
  unique_name_generator
)