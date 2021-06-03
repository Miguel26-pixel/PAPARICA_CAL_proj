cmake_minimum_required(VERSION 3.17)
project(cal_proj)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 14)

include_directories("GraphViewerCpp/SFML/include")
link_directories("GraphViewerCpp/SFML/lib")

add_subdirectory("GraphViewerCpp")

include_directories("GraphViewerCpp/include")

file(GLOB_RECURSE SRC "src/*.cpp" "src/*.h")
add_executable(cal_proj ${SRC} src/Algorithms/AStar.cpp src/Algorithms/headers/AStar.h)

target_link_libraries(${PROJECT_NAME} graphviewer)
