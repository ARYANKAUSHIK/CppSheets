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
#include <iostream>

#include "tablewidget.hh"
#include "math.hh"

TableWidget::TableWidget() {
    this->setColumnCount(1000);
    this->setRowCount(1000);

    connect(this,&TableWidget::cellChanged,this,&TableWidget::onCellChanged);
    connect(this,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(onItemChanged(QTableWidgetItem*)));
}

void TableWidget::setMathItems(QVector<MathItem> items) {
    mathItems = items;
}

void TableWidget::addMathItem(MathItem item) {
    for (int i = 0; i<mathItems.size(); i++) {
        int x = mathItems.at(i).x;
        int y = mathItems.at(i).y;

        if ((x==item.x)&&(y==item.y)) {
            mathItems.removeAt(i);
            break;
        }
    }
    if (item.equation!="=\\") {
        mathItems.push_back(item);
    }
}

QVector<MathItem> TableWidget::allMathItems() {
    return mathItems;
}

void TableWidget::updateMath() {
    Math::updateMath(mathItems,this);
}

bool TableWidget::isMath(int row, int col) {
    bool ret = false;

    for (int i = 0; i<mathItems.size(); i++) {
        int x = mathItems.at(i).x;
        int y = mathItems.at(i).y;

        if ((x==row)&&(y==col)) {
            ret = true;
            break;
        }
    }

    return ret;
}

QString TableWidget::formula(int row, int col) {
    QString str = "";

    for (int i = 0; i<mathItems.size(); i++) {
        int x = mathItems.at(i).x;
        int y = mathItems.at(i).y;

        if ((x==row)&&(y==col)) {
            str = mathItems.at(i).equation;
            break;
        }
    }
    return str;
}

QModelIndexList TableWidget::currentSelectedItems() {
    return this->selectedIndexes();
}

void TableWidget::keyPressEvent(QKeyEvent *event) {
    if ((event->key()==Qt::Key_Enter)||(event->key()==Qt::Key_Return)) {
        QTableWidget::keyPressEvent(event);
        int x = this->currentRow()+1;
        int y = this->currentColumn();
        this->setCurrentCell(x,y);
    }
    QTableWidget::keyPressEvent(event);
}

void TableWidget::onCellChanged() {
    emit cellModified();
}

void TableWidget::onItemChanged(QTableWidgetItem *item) {
    updateMath();
}
