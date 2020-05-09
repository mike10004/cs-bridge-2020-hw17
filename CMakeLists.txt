cmake_minimum_required(VERSION 3.7)
project(hw17)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Werror -Wall")

add_subdirectory("${PROJECT_SOURCE_DIR}/tests" "${PROJECT_SOURCE_DIR}/tests/cmake-build")
add_subdirectory("${PROJECT_SOURCE_DIR}/trees" "${PROJECT_SOURCE_DIR}/trees/cmake-build")
