cmake_minimum_required(VERSION 3.5)
project(govnogame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/")

find_package(SFML 2.4.2 COMPONENTS graphics audio REQUIRED)

include_directories(${SFML_INCLUDE_DIR})


add_executable(govnogame main.cpp Drawer.h Drawer.cpp MathUtil.h Game.cpp Game.h EventProcessor.cpp EventProcessor.h Player.h Player.cpp Wall.h)
target_link_libraries(govnogame sfml-graphics)
