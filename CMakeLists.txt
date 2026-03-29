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

# --- Set the default output folder for binaries ---
set_target_properties(roadgraph PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

# --- Copy data files to the binary folder automatically ---
file(COPY ${PROJECT_SOURCE_DIR}/data DESTINATION ${PROJECT_SOURCE_DIR}/bin)