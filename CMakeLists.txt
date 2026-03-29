cmake_minimum_required(VERSION 3.10)

# Project Name
project(Pathfinders)

# C++17 Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Include headers ---
include_directories(${PROJECT_SOURCE_DIR}/src)

# --- Source files ---
set(SOURCES
    src/main.cpp
    src/parser.cpp
    src/graph.cpp
    src/AStar.cpp
    src/dijkstras.cpp
)

# --- Create executable ---
add_executable(roadgraph ${SOURCES})

# --- Compiler warnings ---
if(MSVC)
    target_compile_options(roadgraph PRIVATE /W4)
else()
    target_compile_options(roadgraph PRIVATE -Wall -Wextra -Wpedantic)
endif()