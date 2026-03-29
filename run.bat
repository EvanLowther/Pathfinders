@echo off
mkdir -p build
cd build
cmake ..
cmake --build .
..\bin\roadgraph.exe
pause