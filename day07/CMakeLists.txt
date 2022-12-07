cmake_minimum_required(VERSION 3.21)
project(day06)

set(CMAKE_CXX_STANDARD 17)

configure_file(data/input.txt input.txt COPYONLY)
configure_file(data/sample.txt sample.txt COPYONLY)

add_executable(day06 main.cpp)
