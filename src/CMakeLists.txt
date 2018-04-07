cmake_minimum_required(VERSION 3.0.0)

set(SRC
    rsc.qrc
    icons.qrc
    main.cxx
    tablewidget.cxx
    sheetwidget.cxx
    window.cxx
    maintoolbar.cxx
    tabwidget.cxx
    actions.cxx
    ribbon.cxx
    cellbar.cxx
    statusbar.cxx
)

set(FORMULA_SRC
	formula/math.cxx
)

set(MENUBAR_SRC
    menubar/filemenu.cxx
)

set(PARSER_SRC
    parser/parser.cxx
    parser/xml_parser.cxx
    parser/xlsx_parser.cxx
    parser/tinyxml2.cpp
)

add_executable(CppSheets 
	${SRC}
	${FORMULA_SRC}
	${MENUBAR_SRC}
	${PARSER_SRC}
)

target_link_libraries(CppSheets
    Qt5::Core
    Qt5::Widgets
    xlnt
)
