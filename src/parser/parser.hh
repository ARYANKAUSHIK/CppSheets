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

#include <QString>
#include <QVector>

#include "sheet_item.hh"

class Parser {
public:
    static void createFile(QString filePath);
	static QStringList pages(QString file);
    static QVector<SheetItem> allItems(QString file, QString page);
    static QVector<MathItem> allMathItems(QString file, QString page);
    static QVector<GraphItem> allGraphItems(QString file, QString page);
    static void createPage(QString file, QString page);
    static bool pageExists(QString file, QString pageName);
    static void removePage(QString file, QString page);
    static void setData(QString file, QString page, QVector<SheetItem> items);
    static void setMathData(QString file, QString page, QVector<MathItem> items);
    static void setGraphData(QString file, QString page, QVector<GraphItem> items);
private:
	static bool isXlsx(QString file);
};
