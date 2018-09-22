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
#include <QTableWidgetItem>

#include "tablewidget_delegate.hh"
#include "tabwidget.hh"

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

    //Controls the brush for currently-selected cells
    } else if (option.state & QStyle::State_Selected) {
        //First, get the current cell and the saved state
        bool saved = TabWidget::currentWidget()->isSaved();
        QTableWidgetItem *item = TabWidget::currentWidget()->currentCell();

        //Set the brush for the background
        painter->save();
        QPen pen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
        int w = pen.width()/2;
        painter->setPen(pen);
        painter->setBrush(item->background());
        painter->drawRect(option.rect.adjusted(w-1,w,-w,-w));
        painter->restore();

        //Set the brush for the text
        //TODO: Somehow add some padding around the text
        QFont font = option.font;
        if (item->font().bold()) {
            font.setBold(true);
        }

        if (item->font().italic()) {
            font.setItalic(true);
        }

        if (item->font().underline()) {
            font.setUnderline(true);
        }

        painter->save();
        QPen pen2(item->textColor());
        painter->setPen(pen2);
        painter->setFont(font);
        painter->drawText(option.rect,Qt::AlignVCenter,index.data().toString());
        painter->restore();

        TabWidget::currentWidget()->setSaved(saved);
    } else {
        QItemDelegate::paint(painter,option,index);
    }
}
