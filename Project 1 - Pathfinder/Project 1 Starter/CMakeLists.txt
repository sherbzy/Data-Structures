cmake_minimum_required(VERSION 3.0)
project(myprogram)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(pathfinder
        main.cpp
        pathfinder.cpp pathfinder.h
        picture.cpp picture.h
        lodepng.cpp lodepng.h)