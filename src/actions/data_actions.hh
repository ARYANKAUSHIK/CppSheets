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

#include <QVector>

#include "../parser/sheet_item.hh"

struct DataItem {
    SheetItem item;
    int original_row;
    int original_col;
};

class DataActions {
public:
    static void load_clipboard(bool cut_data);
    static void paste_data();
private:
    static DataItem clipboard1;
    static QVector<DataItem> clipboard;
    static bool cut;

    static void paste_single_item(int dest_row, int dest_col);
};
