@echo off
title Orca Debug Console
echo === Orca Debug Console ===
echo Waiting for debug output...
type debug.log
:loop
  timeout /t 1 >nul
  type debug.log
  goto loop
