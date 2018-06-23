@echo off

cd build
mkdir winbin

copy src\CppSheets.exe .\winbin
copy src\libxlnt.dll .\winbin

cd winbin
windeployqt --release CppSheets.exe

cd ..