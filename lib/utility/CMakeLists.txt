set(ENV{INCLUDE_DIRS} "$ENV{INCLUDE_DIRS};${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(time_device)
add_subdirectory(container)

set(ENV{INCLUDE_DIRS} "$ENV{INCLUDE_DIRS}")