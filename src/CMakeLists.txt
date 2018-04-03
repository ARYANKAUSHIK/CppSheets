cmake_minimum_required(VERSION 3.0.0)

set(SRC
    rsc.qrc
    icons.qrc
    main.cxx
    parser.cxx
    tinyxml2.cpp
    tablewidget.cxx
    sheetwidget.cxx
    window.cxx
    maintoolbar.cxx
    tabwidget.cxx
    actions.cxx
    ribbon.cxx
    cellbar.cxx
    math.cxx
    statusbar.cxx
    filemenu.cxx
)

add_executable(CppSheets ${SRC})

target_link_libraries(CppSheets
    Qt5::Core
    Qt5::Widgets
    xlnt
)
