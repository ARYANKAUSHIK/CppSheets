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
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <iostream>

#include "tablewidget.hh"
#include "formula/math.hh"

TableWidgetDelegate::TableWidgetDelegate(QObject *parent) : QItemDelegate(parent) {
}

void TableWidgetDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    //Syntax: border:<color>,<width>,<type>
    //Types:
    //solid
    //dash
    //dot
    //dash_dot
    //dash_dot_dot
    if (index.data(Qt::UserRole).toString().startsWith("border:")) {
        QString s = index.data(Qt::UserRole).toString();
        QString colorStr = "NULL";
        QString widthStr = "NULL";
        QString typeStr = "NULL";

        QString current = "";
        int cNo = 1;
        for (int i = 0; i<s.length(); i++) {
            if (s.at(i)==':') {
                for (int j = i+1; j<s.length(); j++) {
                    if (s.at(j)==',') {
                        if (cNo==1) {
                            colorStr = current;
                        } else if (cNo==2) {
                            widthStr = current;
                        } else if (cNo==3) {
                            typeStr = current;
                        }
                        current = "";
                        cNo++;
                    } else {
                        current+=s.at(j);
                    }
                }
            }
        }
        if (cNo==3) {
            typeStr = current;
        }

        if (colorStr=="NULL" || widthStr=="NULL" || typeStr=="NULL") {
            QItemDelegate::paint(painter,option,index);
            return;
        }

        QColor color(colorStr);
        QBrush brush(color);
        int width = QVariant(widthStr).toInt();

        Qt::PenStyle type = Qt::SolidLine;
        if (typeStr=="dash") {
            type = Qt::DashLine;
        } else if (typeStr=="dot") {
            type = Qt::DotLine;
        } else if (typeStr=="dash_dot") {
            type = Qt::DashDotLine;
        } else if (typeStr=="dash_dot_dot") {
            type = Qt::DashDotDotLine;
        }

        painter->save();
        QPen pen(brush, width, type, Qt::SquareCap, Qt::MiterJoin);
        int w = pen.width()/2;
        painter->setPen(pen);
        painter->setBrush(Qt::white);
        painter->drawRect(option.rect.adjusted(w,w,-w,-w));
        painter->restore();

        QItemDelegate::paint(painter,option,index);
    } else if (option.state & QStyle::State_Selected) {
        painter->save();
        QPen pen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
        int w = pen.width()/2;
        painter->setPen(pen);
        painter->setBrush(Qt::white);
        painter->drawRect(option.rect.adjusted(w,w,-w,-w));
        painter->restore();

        painter->save();
        QPen pen2(Qt::black);
        painter->setPen(pen2);
        painter->setFont(option.font);
        painter->drawText(option.rect,Qt::AlignCenter,index.data().toString());
        painter->restore();
    } else {
        QItemDelegate::paint(painter,option,index);
    }
}

TableWidget::TableWidget() {
    this->setColumnCount(1000);
    this->setRowCount(1000);
    this->loadHeaders();

    this->setItemDelegate(new TableWidgetDelegate(this));

    connect(this,&TableWidget::cellChanged,this,&TableWidget::onCellChanged);
    connect(this,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(onItemChanged(QTableWidgetItem*)));
    connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(onCellClicked(int,int)));
}

void TableWidget::loadHeaders() {
    QStringList letters;
    QStringList headers;

    QFile file(":/headers.txt");
    if (file.open(QFile::ReadOnly)) {
        QTextStream reader(&file);
        while (!reader.atEnd()) {
            letters.push_back(reader.readLine());
        }
    }

    int index = 0;
    int len = letters.length();
    int currentFirst = -1;
    for (int i = 0; i<1000; i++) {
        if (i>0) {
            if (i%len==0) {
                currentFirst++;
                index = 0;
            }
        }
        QString result = "";
        if (currentFirst>-1) {
            if (currentFirst==len) {
                break;
            }
            result+=letters.at(currentFirst);
        }
        result+=letters.at(index);
        headers.push_back(result);
        index++;
    }

    this->setHorizontalHeaderLabels(headers);
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

void TableWidget::onCellClicked(int row, int col) {
}

void TableWidget::onItemChanged(QTableWidgetItem *item) {
    if (item->text().startsWith("=")) {
        MathItem mitem;
        mitem.x = item->row();
        mitem.y = item->column();
        mitem.equation = item->text();
        addMathItem(mitem);
    }
    updateMath();
}
