// This file is part of CppSheets.
//
// Copyright 2018 Patrick Flynn <patrick_dev2000@outlook.com>
//
// CppSheets is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CppSheets is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CppSheets. If not, see <https://www.gnu.org/licenses/>.
#pragma once

#include <QMainWindow>
#include <QCloseEvent>

#include "menubar/filemenu.hh"
#include "menubar/format_menu.hh"
#include "menubar/cellmenu.hh"
#include "menubar/graph_menu.hh"
#include "menubar/helpmenu.hh"
#include "statusbar.hh"
#include "graphwin.hh"

class Window : public QMainWindow {
    Q_OBJECT
public:
    Window();
    ~Window();
    static void setCurrentPath(QString path);
    static void setCurrentSaved(bool saved);
    static void showGraphWin();
    static bool checkSave();

    static GraphWin *graphWin;
protected:
    void closeEvent(QCloseEvent *event);
private:
    FileMenu *filemenu;
    FormatMenu *formatMenu;
    CellMenu *cellMenu;
    GraphMenu *graphMenu;
    HelpMenu *helpMenu;
    static StatusBar *statusbar;
};
