@echo off
"%~dp0\cppcheck.exe" --template="{file}({line}): warning:  ({severity})  {message}" %*
