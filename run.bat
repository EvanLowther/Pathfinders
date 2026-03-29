@echo off

REM Create build folder if it doesn't exist
if not exist build (
    mkdir build
)

REM Go into build directory
cd build

REM Run CMake
cmake ..

REM Build project
cmake --build .

REM Run executable
roadgraph.exe

REM Go back to root
cd ..