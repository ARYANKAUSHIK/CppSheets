## CppSheets

#### Introduction
CppSheets is a simple spreadsheet application that I work on as a hobby project. For more information about the project and the program itself, see the wiki.

#### Features
Basic formatting (bold, italic, underline text; cell background color; text color; cell borders)   
Cell merge   
Custom XML-based file format   
Basic xlsx (MS Excel) support   
Formula support   

For more information, see the wiki.

#### Building
Building is very easy; the only external dependency required is Qt5 (Core, Widgets, Gui). To build, simply run CMake and Make. Note: you should probably use G++ to build this program; I tried using Clang, and it failed while building the xlnt library (Update: Clang seems to be working now after a minor change in the xlnt library; this was only tested on MacOS though).

#### Platform Support
CppSheets is fully supported on Linux, Windows, and MacOS. It should work on other systems as well. I will list them here as I test them.

#### Licensing
CppSheets is licensed under BSD-3.   
The built-in TinyXML2 library is licensed under the zlib license.   
The included xlnt library is licensed under MIT.   
Qt5 is licensed under LGPL.   
The included Oxygen icons are licensed under LGPL.   

See the wiki for more information.


