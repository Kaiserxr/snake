@echo off
cd /d "%~dp0"
C:\raylib\w64devkit\bin\g++.exe snake.cpp -o snake.exe -I C:/raylib/raylib/src -L C:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm
if errorlevel 1 (
    pause
    exit /b
)
start snake.exe