cmake_minimum_required(VERSION 3.0.0)

set(SRC
	main.cxx
	parser.cxx
	tinyxml2.cpp
        tablewidget.cxx
        sheetwidget.cxx
        window.cxx
        maintoolbar.cxx
        tabwidget.cxx
        rsc.qrc
        actions.cxx
        ribbon.cxx
        homebar.cxx
        math.cxx
        statusbar.cxx
)

add_executable(CppSheets ${SRC})

target_link_libraries(CppSheets
	Qt5::Core
	Qt5::Widgets
)
