// Copyright 2018 Patrick Flynn
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//	this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this
//	list of conditions and the following disclaimer in the documentation and/or
//	other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may
//	be used to endorse or promote products derived from this software
//	without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

