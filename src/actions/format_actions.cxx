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
#include <QColorDialog>

#include "format_actions.hh"
#include "../tabwidget.hh"
#include "../parser/parser.hh"
#include "../sheetwidget.hh"
#include "../dialogs/border_dialog.hh"

void FormatActions::bold() {
    SheetWidget *sheet = TabWidget::currentWidget();
    QTableWidgetItem *item = sheet->currentCell();
    QFont font = item->font();
    if (font.bold()) {
        font.setBold(false);
    } else {
        font.setBold(true);
    }
    item->setFont(font);
}

void FormatActions::italic() {
    SheetWidget *sheet = TabWidget::currentWidget();
    QTableWidgetItem *item = sheet->currentCell();
    QFont font = item->font();
    if (font.italic()) {
        font.setItalic(false);
    } else {
        font.setItalic(true);
    }
    item->setFont(font);
}

void FormatActions::underline() {
    SheetWidget *sheet = TabWidget::currentWidget();
    QTableWidgetItem *item = sheet->currentCell();
    QFont font = item->font();
    if (font.underline()) {
        font.setUnderline(false);
    } else {
        font.setUnderline(true);
    }
    item->setFont(font);
}

void FormatActions::bgColor() {
    QColor color = QColorDialog::getColor();
    SheetWidget *current = TabWidget::currentWidget();
    if (current->currentTable()->currentSelectedItems().size()==1) {
        TabWidget::currentWidget()->currentCell()->setBackgroundColor(color);
    } else {
        auto list = current->currentTable()->currentSelectedItems();
        for (auto item : list) {
            int col = item.column();
            int row = item.row();

            QTableWidgetItem *tItem = current->currentTable()->item(row,col);
            if (tItem==nullptr) {
                tItem = new QTableWidgetItem();
                current->currentTable()->setItem(row,col,tItem);
            }
            tItem->setBackgroundColor(color);
        }
    }
}

void FormatActions::fgColor() {
    QColor color = QColorDialog::getColor(Qt::black);
    SheetWidget *current = TabWidget::currentWidget();
    if (current->currentTable()->currentSelectedItems().size()==1) {
        TabWidget::currentWidget()->currentCell()->setTextColor(color);
    } else {
        auto list = current->currentTable()->currentSelectedItems();
        for (auto item : list) {
            int col = item.column();
            int row = item.row();

            QTableWidgetItem *tItem = current->currentTable()->item(row,col);
            if (tItem==nullptr) {
                tItem = new QTableWidgetItem();
                current->currentTable()->setItem(row,col,tItem);
            }
            tItem->setTextColor(color);
        }
    }
}

void FormatActions::merge() {
    TabWidget::currentWidget()->mergeSelected();
}

void FormatActions::unMerge() {
    TabWidget::currentWidget()->unMergeSelected();
}

void FormatActions::insertCol() {
    auto current = TabWidget::currentWidget();
    int col = current->currentCell()->column();
    current->currentTable()->insertColumn(col+1);
    current->currentTable()->loadHeaders();
    current->setSaved(false);
}

void FormatActions::insertRow() {
    auto current = TabWidget::currentWidget();
    int row = current->currentCell()->row();
    current->currentTable()->insertRow(row+1);
    current->setSaved(false);
}

void FormatActions::setFontFamily(QString family) {
    auto current = TabWidget::currentWidget();
    auto list = current->currentTable()->currentSelectedItems();

    if (list.size()==1) {
        QFont font = current->currentCell()->font();
        font.setFamily(family);
        current->currentCell()->setFont(font);
    } else {
        for (auto c : list) {
            QTableWidgetItem *item = current->currentTable()->item(c.row(),c.column());
            if (item==nullptr) {
                item = new QTableWidgetItem;
            }

            QFont font = item->font();
            font.setFamily(family);
            item->setFont(font);

            current->currentTable()->setItem(c.row(),c.column(),item);
        }
    }
}

void FormatActions::setFontSize(int size) {
    auto current = TabWidget::currentWidget();
    auto list = current->currentTable()->currentSelectedItems();

    if (list.size()==1) {
        QFont font = current->currentCell()->font();
        font.setPointSize(size);
        current->currentCell()->setFont(font);
    } else {
        for (auto c : list) {
            QTableWidgetItem *item = current->currentTable()->item(c.row(),c.column());
            if (item==nullptr) {
                item = new QTableWidgetItem;
            }

            QFont font = item->font();
            font.setPointSize(size);
            item->setFont(font);

            current->currentTable()->setItem(c.row(),c.column(),item);
        }
    }
}

void FormatActions::dspBorderDialog() {
    BorderDialog dialog;
    dialog.exec();
}

