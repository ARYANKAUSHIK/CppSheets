cmake_minimum_required(VERSION 3.0.0)
project(CppSheets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS
	Core
	Widgets
	Gui
)

add_compile_options(-std=c++11)

add_subdirectory(src)
