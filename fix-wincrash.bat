@echo off

cd build\src

del libgraph.dll
del libmath.dll
del libxlnt.dll

cd ..

copy libgraph\libgraph.dll .\src
copy libmath\libmath.dll .\src
copy xlnt\source\libxlnt.dll .\src

cd ..