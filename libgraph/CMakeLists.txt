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

set(SRC
    main.cxx
    bargraph.cxx
)

add_executable(graph_test WIN32 ${SRC})

target_link_libraries(graph_test
    Qt5::Core
    Qt5::Widgets
    Qt5::Charts
)