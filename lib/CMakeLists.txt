set(ENV{INCLUDE_DIRS} "$ENV{INCLUDE_DIRS};${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(utility)
add_subdirectory(input_device)
add_subdirectory(command_device)
add_subdirectory(game)