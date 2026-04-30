@echo off
REM Simple batch Makefile for Orca
setlocal
if not exist build mkdir build
gcc src\main.c -o build\Orca.exe -mwindows -lcomctl32
if %errorlevel% neq 0 (
  echo Build failed.
  exit /b %errorlevel%
)
echo Build succeeded.
cmd /k