cmake_minimum_required(VERSION 3.0.0)

set(SRC
    rsc.qrc
    icons.qrc
    main.cxx
    tablewidget.cxx
    tablewidget_delegate.cxx
    sheetwidget.cxx
    window.cxx
    maintoolbar.cxx
    tabwidget.cxx
    statusbar.cxx
)

set(ACTIONS_SRC
    actions/file_actions.cxx
    actions/format_actions.cxx
    actions/data_actions.cxx
)

set(DIALOGS_SRC
    dialogs/border_dialog.cxx
    dialogs/graph_list_dialog.cxx
    dialogs/graph_dialog.cxx
)

set(FORMULA_SRC
    formula/math.cxx
    formula/formula_utils.cxx
    formula/math_funcs.cxx
    formula/str_funcs.cxx
)

set(GRAPH_SRC
    graph/bar_graph_win.cxx
)

set(MENU_SRC
    menu/page_menu.cxx
)

set(MENUBAR_SRC
    menubar/filemenu.cxx
    menubar/format_menu.cxx
    menubar/cellmenu.cxx
    menubar/helpmenu.cxx
    menubar/graph_menu.cxx
)

set(PARSER_SRC
    parser/parser.cxx
    parser/xml_parser.cxx
    parser/xlsx_parser.cxx
    parser/csv_parser.cxx
    parser/tinyxml2.cpp
)

set(SRC_ALL
    ${SRC}
    ${ACTIONS_SRC}
    ${DIALOGS_SRC}
    ${FORMULA_SRC}
    ${GRAPH_SRC}
    ${MENU_SRC}
    ${MENUBAR_SRC}
    ${PARSER_SRC}
)

set(WIN_SRC
    ${SRC_ALL}
    appicon.rc
)

if (WIN32)
    add_executable(CppSheets WIN32 ${WIN_SRC})
elseif(APPLE)
    add_executable(CppSheets MACOSX_BUNDLE ${SRC_ALL})
else()
    add_executable(CppSheets ${SRC_ALL})
endif()

target_link_libraries(CppSheets
    Qt5::Core
    Qt5::Widgets
    Qt5::Charts
    xlnt
    graph
)

if (UNIX)
    if (APPLE)
        install(TARGETS CppSheets BUNDLE DESTINATION /Applications)
    endif()
endif()
