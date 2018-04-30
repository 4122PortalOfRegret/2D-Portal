cmake_minimum_required(VERSION 3.5)
project(SDL2Test)
set(CMAKE_CXX_STANDARD 11)
find_package(SDL2 REQUIRED)
include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})
set( sources
        main.cpp
        block.cpp
        player.cpp
        portal.cpp
        EndZoneWall.cpp
)
add_executable(SDL2Test ${sources})
target_link_libraries(SDL2Test ${SDL2_LIBRARIES})
