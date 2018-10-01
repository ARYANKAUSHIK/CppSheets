cmake_minimum_required(VERSION 3.0.0)
project(libgraph)

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

set(SRC
    bargraph.cxx
)

add_library(graph SHARED ${SRC})

target_link_libraries(graph
    Qt5::Core
    Qt5::Widgets
    Qt5::Charts
)