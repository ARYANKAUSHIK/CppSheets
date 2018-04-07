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
#include <QHeaderView>
#include <QTableWidgetItem>

#include "formula_utils.hh"
#include "../tabwidget.hh"

QString FormulaUtils::transAndGetContent(QString loco) {
    QString ret = "";

    if (loco.at(0).isNumber() || loco.at(0)=='(' || loco.at(0)==')') {
        ret = loco;
        return ret;
    }

    QString letter = "";
    QString no = "";
    for (int i = 0; i<loco.length(); i++) {
        if (loco.at(i).isLetter()) {
            letter+=loco.at(i);
        } else if (loco.at(i).isNumber()) {
            no+=loco.at(i);
        }
    }

    int x = 0;
    int y = QVariant(no).toInt();

    QTableWidget *current = TabWidget::currentWidget()->currentTable();
    int count = current->horizontalHeader()->count();
    for (int i = 0; i<count; i++) {
        if (current->horizontalHeaderItem(i)->text()==letter) {
            x = i;
            break;
        }
    }

    y--;

    QTableWidgetItem *item = current->item(y,x);
    if (item==nullptr) {
        return ret;
    }
    ret = item->text();

    return ret;
}

double FormulaUtils::solve(QStringList objects) {
    double result = QVariant(objects.at(0)).toDouble();

    int len = objects.length();
    for (int i = 1; i<len; i+=2) {
        double no = QVariant(objects.at(i+1)).toDouble();
        QString op = objects.at(i);
        if (op=="+") {
            result+=no;
        } else if (op=="-") {
            result-=no;
        } else if (op=="*") {
            result*=no;
        } else if (op=="/") {
            result/=no;
        }
    }

    return result;
}

