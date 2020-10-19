cmake_minimum_required(VERSION 3.0.0)
project(partC VERSION 0.1.0)

set(MTM_FLAGS_DEBUG "-std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDBUG")

set(CMAKE_CXX_FLAGS ${MTM_FLAGS_DEBUG})

add_executable(final_proj Calculator.cpp Edge.cpp Vertex.cpp Graph.cpp Auxiliries_main.cpp Code_for_python.cpp main.cpp)