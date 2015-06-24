cmake_minimum_required(VERSION 2.5)

enable_testing()

find_program(VERIFY verify)
find_program(CBMC cbmc)
find_program(ASTYLE astyle)

file(GLOB_RECURSE FORMAT_FILES src/*.c src/*.h)
add_custom_target(format COMMAND ${ASTYLE} ${FORMAT_FILES} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

project(px4vv C)

set(CMAKE_C_FLAGS "-g")

include_directories(src)

add_subdirectory(src/hal/arch/posix)

add_subdirectory(src/fsm_main_state)

