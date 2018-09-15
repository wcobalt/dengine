cmake_minimum_required(VERSION 3.12)
project(Dengine)

set(CMAKE_CXX_STANDARD 17)

add_executable(Dengine main.cpp WindowAccessors/WindowAccessorX.cpp WindowAccessors/WindowAccessorX.h WindowAccessor.cpp WindowAccessor.h)