@echo off
REM Simple batch Makefile for Orca
setlocal
if not exist build mkdir build
powershell -NoProfile -Command "& { $sw=[diagnostics.stopwatch]::StartNew(); & gcc 'src\main.c' -o 'build\Orca.exe' -mwindows -lcomctl32; if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }; & gcc 'src\img2carray.c' -o 'build\IMG2CARRAY.exe'; $code=$LASTEXITCODE; $sw.Stop(); if ($code -ne 0) { Write-Host 'Build failed.'; Write-Host ('Elapsed: {0} ms' -f $sw.Elapsed.TotalMilliseconds.ToString('F3')); exit $code } else { Write-Host 'Build succeeded.'; Write-Host ('Elapsed: {0} ms' -f $sw.Elapsed.TotalMilliseconds.ToString('F3')); exit 0 } }"
cmd /k
if %errorlevel% neq 0 (
  exit /b %errorlevel%
  cmd /k
)
