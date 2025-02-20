cmake_minimum_required(VERSION 3.26)
project(worm)

set(CMAKE_CXX_STANDARD 23)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

add_executable(untitled8 main.cpp
        worm.cpp
        worm.hpp
        screen.cpp
        screen.hpp
        getChar.cpp
        getChar.hpp)

target_link_libraries(untitled8 ${CURSES_LIBRARIES})