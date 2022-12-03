cmake_minimum_required(VERSION 3.21)
project(day03)

set(CMAKE_CXX_STANDARD 17)

configure_file(data/input.txt input.txt COPYONLY)
configure_file(data/sample.txt sample.txt COPYONLY)

add_executable(day03 main.cpp)
