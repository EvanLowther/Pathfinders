@echo off
cd build
cmake ..
cmake --build .
..\bin\roadgraph.exe
pause