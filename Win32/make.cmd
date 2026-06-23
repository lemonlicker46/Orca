@echo off
REM Simple batch Makefile for Orca
setlocal
if not exist build mkdir build
rem Enable a broad set of strict compiler warnings and treat them as errors
set "GCC_WARN_FLAGS=-std=c11 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wformat=2 -Wcast-qual -Wpointer-arith -Wmissing-prototypes -Wmissing-declarations -Wstrict-prototypes -Wold-style-definition -Wundef -Wswitch-enum -Wduplicated-cond -Wlogical-op -Wfloat-equal -Wcast-align -fno-common"
set "GCC_OTHER_FLAGS=-g -O0"

powershell -NoProfile -Command "& { $sw=[diagnostics.stopwatch]::StartNew(); & gcc 'src\main.c' 'src\compiler.c' -o 'build\Orca.exe' -mwindows %GCC_WARN_FLAGS% %GCC_OTHER_FLAGS% -lcomctl32 -lshell32; if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }; $code=$LASTEXITCODE; $sw.Stop(); if ($code -ne 0) { Write-Host 'Build failed.'; Write-Host ('Elapsed: {0} ms' -f $sw.Elapsed.TotalMilliseconds.ToString('F3')); exit $code } else { Write-Host 'Build succeeded.'; Write-Host ('Elapsed: {0} ms' -f $sw.Elapsed.TotalMilliseconds.ToString('F3')); exit 0 } }"
cmd /k
if %errorlevel% neq 0 (
  exit /b %errorlevel%
  cmd /k
)
