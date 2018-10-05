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

#include <QDockWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QTreeWidget>
#include <QListWidget>
#include <QCheckBox>

#include "parser/sheet_item.hh"

class GraphWin : public QDockWidget {
    Q_OBJECT
public:
    GraphWin();
    void loadGraphData(GraphItem item);
private:
    QFrame *parent, *nameWidget, *addSetWidget, *categoryWidget;
    QVBoxLayout *parentLayout;
    QHBoxLayout *nameLayout, *setLayout, *categoryLayout;
    QLineEdit *graphName, *name, *range, *category;
    QPushButton *set, *addCategory, *showGraph;
    QTabWidget *tabs;
    QTreeWidget *sets;
    QListWidget *categories;
    QCheckBox *saveGraph;

    void writeGraphData();
    QStringList getCategories();
private slots:
    void onAddSet();
    void onAddCategory();
    void onShowGraph();
};
