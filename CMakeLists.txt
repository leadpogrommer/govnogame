cmake_minimum_required(VERSION 3.15)
project(govnogame)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SDL2_LIBRARY /usr/lib/libSDL2.so)
add_executable(govnogame main.cpp Drawer.h Drawer.cpp MathUtil.h Game.cpp Game.h)
target_link_libraries(govnogame ${SDL2_LIBRARY})