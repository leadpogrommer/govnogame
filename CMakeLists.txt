cmake_minimum_required(VERSION 3.5)
project(govnogame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/")

find_package(SFML 2.5.1 COMPONENTS graphics audio network REQUIRED)

find_package(Threads)

include_directories(${SFML_INCLUDE_DIR})

file(GLOB GG_SOURCES *.cpp)
file(GLOB GG_HEADERS *.h)

get_filename_component(gmain ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ABSOLUTE)
get_filename_component(gserver ${CMAKE_CURRENT_SOURCE_DIR}/servermain.cpp ABSOLUTE)

list(REMOVE_ITEM GG_SOURCES ${gserver} ${gmain})

message(${GG_SOURCES})




add_executable(govnogame main.cpp ${GG_HEADERS} ${GG_SOURCES})
add_executable(govnoserver servermain.cpp ${GG_HEADERS} ${GG_SOURCES})
target_link_libraries(govnogame sfml-graphics sfml-network ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(govnoserver sfml-graphics sfml-network ${CMAKE_THREAD_LIBS_INIT})
