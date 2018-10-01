cmake_minimum_required(VERSION 3.0.0)
project(CppSheets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Widgets
    Gui
    Charts
)

add_compile_options(-std=c++14)
include_directories(xlnt/include)
include_directories(libgraph)

add_subdirectory(xlnt)
add_subdirectory(libgraph)
add_subdirectory(src)
