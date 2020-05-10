cmake_minimum_required(VERSION 3.5)
project(govnogame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/")

find_package(SFML 2.4.2 COMPONENTS graphics audio network REQUIRED)

find_package(Threads)

include_directories(${SFML_INCLUDE_DIR})

file(GLOB GG_SOURCES *.cpp)
file(GLOB GG_HEADERS *.h)

set(CMAKE_CXX_COM)

add_executable(govnogame ${GG_HEADERS} ${GG_SOURCES})
target_link_libraries(govnogame sfml-graphics sfml-network ${CMAKE_THREAD_LIBS_INIT})
