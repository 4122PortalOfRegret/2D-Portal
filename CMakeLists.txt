cmake_minimum_required(VERSION 3.5)
project(2-D_Portal)
set(CMAKE_CXX_STANDARD 11)
find_package(SDL2 REQUIRED)
include_directories(2-D_Portal ${SDL2_INCLUDE_DIRS})
set( sources
        main.cpp
        block.cpp
        player.cpp
        portal.cpp
        EndZoneWall.cpp
)
add_executable(2-D_Portal ${sources})
target_link_libraries(2-D_Portal ${SDL2_LIBRARIES})
