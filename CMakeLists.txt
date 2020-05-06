cmake_minimum_required(VERSION 3.15)
project(govnogame)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL_ttf REQUIRED)


include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIR})

set(SDL2_LIBRARY /usr/lib/libSDL2.so)
add_executable(govnogame main.cpp Drawer.h Drawer.cpp MathUtil.h Game.cpp Game.h EventProcessor.cpp EventProcessor.h)
target_link_libraries(govnogame ${SDL2_LIBRARY} "/usr/lib/libSDL_ttf.so")