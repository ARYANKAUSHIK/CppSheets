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
#include <iostream>

#include "math.hh"
#include "../sheetwidget.hh"
#include "../tabwidget.hh"

void Math::updateMath(QVector<MathItem> mathItems, TableWidget *table) {
    for (int i = 0; i<mathItems.size(); i++) {
        QString equ = mathItems.at(i).equation;
        QString newEqu = equ.remove(0,1);

        if ((newEqu.startsWith("add"))||(newEqu.startsWith("sub"))
                ||(newEqu.startsWith("mp"))||(newEqu.startsWith("div"))) {
            applyBulkFormula(mathItems.at(i),table);
        } else {
            applyColumnFormula(mathItems.at(i),table);
        }
    }
}

void Math::applyBulkFormula(MathItem mathItem, TableWidget *table) {
    int x = mathItem.x;
    int y = mathItem.y;
    QString equ = mathItem.equation;
    QString newEqu = equ.remove(0,1);

    bool parseOp = true;
    QString opStr = "";
    OPERATION op = OPERATION::ADD;
    bool isSecond = false;
    bool parse = false;
    bool foundComma = false;
    QString strCx = "";
    QString strCy = "";
    int cx = 0;
    int cy = 0;
    Cell startCell, endCell;
    double result = 0;

    for (int i = 0; i<newEqu.size(); i++) {
        QChar c = newEqu.at(i);
        if (c=='>') {
            parseOp = false;
            if (opStr=="add") {
                op = OPERATION::ADD;
            } else if (opStr=="sub") {
                op = OPERATION::SUB;
            } else if (opStr=="mp") {
                op = OPERATION::MP;
            } else if (opStr=="div") {
                op = OPERATION::DIV;
            }
        } else if (c=='(') {
            parse = true;
        } else if (c==')') {
            cx = QVariant(strCx).toInt();
            cy = QVariant(strCy).toInt();
            cx--;
            cy--;

            if (isSecond) {
                endCell.x = cx;
                endCell.y = cy;
            } else {
                startCell.x = cx;
                startCell.y = cy;
            }

            parse = false;
            foundComma = false;
            strCx = strCy = "";
        } else if (c==':') {
            isSecond = true;
        } else if (c==',') {
            foundComma = true;
        } else {
            if (parseOp) {
                opStr+=c;
            } else {
                if (parse) {
                    if (foundComma) {
                        strCx+=c;
                    } else {
                        strCy+=c;
                    }
                }
            }
        }
    }

    bool getRows = true;
    int start = startCell.y;
    int end = endCell.y;
    if ((startCell.y)==(endCell.y)) {
        getRows = false;
        start = startCell.x;
        end = endCell.x;
    }

    QStringList noStrList;

    for (int i = start; i<(end+1); i++) {
        QTableWidgetItem *item;
        if (getRows) {
            item = table->item(i,startCell.x);
        } else {
            item = table->item(startCell.y,i);
        }
        if (item==nullptr) {
            continue;
        }
        noStrList.push_back(item->text());
    }

    if (noStrList.size()==0) {
        return;
    }

    int s = 0;
    if ((op==OPERATION::MP)||(op==OPERATION::DIV)) {
        result = QVariant(noStrList.at(0)).toDouble();
        s = 1;
    }
    for (int i = s; i<noStrList.size(); i++) {
        double current = QVariant(noStrList.at(i)).toDouble();

        if (op==OPERATION::ADD) {
            result+=current;
        } else if (op==OPERATION::SUB) {
            result-=current;
        } else if (op==OPERATION::MP) {
            result*=current;
        } else if (op==OPERATION::DIV) {
            result/=current;
        }
    }

    QString strResult = QVariant(result).toString();
    QTableWidgetItem *item = table->item(x,y);
    if (item==nullptr) {
        item = new QTableWidgetItem;
    }
    item->setText(strResult);
    table->setItem(x,y,item);
}

void Math::applyColumnFormula(MathItem mathItem, TableWidget *table) {
    int x = mathItem.x;
    int y = mathItem.y;
    QString equ = mathItem.equation;
    equ = equ.remove(0,1);

    QString no;
    QStringList objects;

    for (int i = 0; i<equ.length(); i++) {
        if (equ.at(i)=='+') {
            no = transAndGetContent(no);
            objects.push_back(no);
            objects.push_back("+");
            no = "";
        } else if (equ.at(i)=='-') {
            no = transAndGetContent(no);
            objects.push_back(no);
            objects.push_back("-");
            no = "";
        } else if (equ.at(i)=='*') {
            no = transAndGetContent(no);
            objects.push_back(no);
            objects.push_back("*");
            no = "";
        } else if (equ.at(i)=='/') {
            no = transAndGetContent(no);
            objects.push_back(no);
            objects.push_back("/");
            no = "";
        } else {
            no+=equ.at(i);
        }
    }
    no = transAndGetContent(no);
    objects.push_back(no);

    double result = solve(objects);

    QTableWidgetItem *item = table->item(x,y);
    if (item==nullptr) {
        item = new QTableWidgetItem;
    }
    QString resultStr = QString::number(result);
    item->setText(resultStr);
    table->setItem(x,y,item);
}

double Math::solve(QStringList objects) {
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

bool Math::isOperator(QString s) {
    if (s=="+") {
        return true;
    } else if (s=="-") {
        return true;
    } else if (s=="*") {
        return true;
    } else if (s=="/") {
        return true;
    } else {
        return false;
    }
}

QString Math::transAndGetContent(QString loco) {
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
