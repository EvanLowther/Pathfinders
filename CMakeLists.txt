cmake_minimum_required(VERSION 3.10)

# Pennsylvania-Paths
project(Pathfinders)

#C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Include header files from src/
include_directories(src)

# Create executable
add_executable(main
    src/main.cpp
    src/parser.cpp
    src/graph.cpp
)