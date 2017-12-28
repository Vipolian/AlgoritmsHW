cmake_minimum_required(VERSION 3.8.2)
project(HashMap)

set(CMAKE_CXX_STANDARD 14)

add_executable(HashMap main.cpp ChainTH/ChainHT.hpp LineHT/LineHT.hpp DoubleHT/DoubleHT.hpp ChainTH/ChainHT.cpp DoubleHT/DoubleHT.cpp LineHT/LineHT.cpp)