cmake_minimum_required(VERSION 3.10)

# Project Name
project(Pathfinders)

# C++17 Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header files from the src directory
include_directories(src)

# Define the source files explicitly for clarity
set(SOURCES
    src/main.cpp
    src/parser.cpp
    src/graph.cpp
    src/graph.h
    src/parser.h
        src/AStar.h
        src/AStar.cpp
)

# Create the executable named 'roadgraph' 
# (Matches your launch.json configuration)
add_executable(roadgraph ${SOURCES}
    src/dijkstras.h src/dijkstras.cpp)

# Optional: Add compiler warnings to help catch bugs early
if(MSVC)
    target_compile_options(roadgraph PRIVATE /W4)
else()
    target_compile_options(roadgraph PRIVATE -Wall -Wextra)
endif()