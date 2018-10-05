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

#include <QTableWidget>
#include <QItemDelegate>
#include <QPainter>
#include <QVector>
#include <QTableWidgetItem>
#include <QModelIndexList>
#include <QKeyEvent>

#include "parser/xml_parser.hh"

class TableWidget : public QTableWidget {
    Q_OBJECT
public:
    TableWidget();
    void loadHeaders();
    void setMathItems(QVector<MathItem> items);
    void addMathItem(MathItem item);
    QVector<MathItem> allMathItems();
    void updateMath();
    bool isMath(int row, int col);
    QString formula(int row, int col);
    QModelIndexList currentSelectedItems();
    void addGraphItem(GraphItem item);
    QVector<GraphItem> allGraphItems();
private:
    void keyPressEvent(QKeyEvent *event);
private:
    QVector<MathItem> mathItems;
    QVector<GraphItem> graphItems;
private slots:
    void onCellChanged();
    void onItemChanged(QTableWidgetItem *item);
    void onCellClicked(int row, int col);
signals:
    void cellModified();
};
