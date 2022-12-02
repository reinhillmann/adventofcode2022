cmake_minimum_required(VERSION 3.21)
project(day01)

set(CMAKE_CXX_STANDARD 17)

configure_file(data/input.txt input.txt COPYONLY)

add_executable(day01 main.cpp)
