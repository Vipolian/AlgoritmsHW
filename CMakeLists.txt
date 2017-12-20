cmake_minimum_required(VERSION 3.9)
project(HashMap)

set(CMAKE_CXX_STANDARD 11)

add_executable(HashMap main.cpp ChainHT.hpp LineHT.hpp DoubleHT.hpp ChainHT.cpp DoubleHT.cpp LineHT.cpp)