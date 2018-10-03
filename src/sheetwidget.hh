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

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTabWidget>
#include <QString>
#include <QToolButton>
#include <QVector>
#include <QStringList>
#include <QTableWidgetItem>

#include "parser/xml_parser.hh"
#include "tablewidget.hh"

class SheetWidget : public QWidget {
    Q_OBJECT
public:
    SheetWidget(QString path);
    ~SheetWidget();
    void loadFile();
    QStringList allPages();
    void setData(QVector<SheetItem> itemList, TableWidget *table);
    QVector<SheetItem> data(QString page);
    QVector<MathItem> mathData(QString page);
    void setFile(QString path);
    QString file();
    bool isUntitled();
    void setSaved(bool s);
    bool isSaved();
    void mergeSelected();
    void unMergeSelected();
    TableWidget *currentTable();
    QTableWidgetItem *currentCell();
    QString currentPage();
    void insertPage();
    void renamePage(int index);
    int currentIndex();
private:
    QVBoxLayout *layout;
    QLineEdit *currentData;
    QTabWidget *tabs;
    QToolButton *addTab;
    QString filePath;
    bool saved = true;
    void addNewTab(int no);
private slots:
    void onCellChanged();
    void onCellLocoChanged(QTableWidgetItem *current, QTableWidgetItem *last);
    void onCurrentDataEnterPressed();
    void onAddTabClicked();
    void onTabDoubleClick(int index);
    void onTabClose(int index);
    void onCustomContextMenu(QPoint pos);
};
