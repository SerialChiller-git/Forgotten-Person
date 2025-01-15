@echo off
echo Building...
cmake --build build
echo Running...
cd build/bin/Debug/
start Forgotten_Person.exe
cd ../../..