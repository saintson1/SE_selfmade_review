set(ENV{INCLUDE_DIRS} "$ENV{INCLUDE_DIRS};${CMAKE_CURRENT_SOURCE_DIR}")

set(INCLUDE_DIRS_LIST $ENV{INCLUDE_DIRS})
string(REPLACE ";" ";" INCLUDE_DIRS_LIST "${INCLUDE_DIRS_LIST}")


add_executable(lsm_container_test lsm_container_test.cpp)

target_include_directories(lsm_container_test PRIVATE
  ${INCLUDE_DIRS_LIST}
)

target_link_libraries(lsm_container_test PRIVATE 
  unique_name_generator
)