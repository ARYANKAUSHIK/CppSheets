#include <iostream>

#include "math.hh"

void Math::updateMath(QVector<MathItem> mathItems, TableWidget *table) {
    for (int i = 0; i<mathItems.size(); i++) {
        QString equ = mathItems.at(i).equation;
        QString newEqu = equ.remove(0,1);

        if ((newEqu.startsWith("add"))||(newEqu.startsWith("sub"))
                ||(newEqu.startsWith("mp"))||(newEqu.startsWith("div"))) {

        } else {
            applyColumnFormula(mathItems.at(i),table);
        }
    }
}

void Math::applyColumnFormula(MathItem mathItem, TableWidget *table) {
    int x = mathItem.x;
    int y = mathItem.y;
    QString equ = mathItem.equation;

    QString newEqu = equ.remove(0,1);
    bool foundSign = false;
    bool parse = false;
    bool foundComma = false;
    bool inBracket = false;
    double result = 0;
    OPERATION op = OPERATION::ADD;
    QString cxStr = "";
    QString cyStr = "";
    int cx = 0;
    int cy = 0;
    double no = 0;

    std::cout << newEqu.toStdString() << std::endl;

    for (int i = 0; i<newEqu.size(); i++) {
        QChar c = newEqu.at(i);
        if (c=='+') {
            foundSign = true;
            op = OPERATION::ADD;
        } else if (c=='-') {
            foundSign = true;
            op = OPERATION::SUB;
        } else if (c=='x') {
            foundSign = true;
            op = OPERATION::MP;
        } else if (c=='/') {
            foundSign = true;
            op = OPERATION::DIV;
        } else if (c=='[') {
            inBracket = true;
            parse = true;
        } else if (c=='(') {
            parse = true;
        } else if ((c==')')||(c==']')) {
            cx = QVariant(cxStr).toInt();
            cy = QVariant(cyStr).toInt();
            cx--;
            cy--;

            QTableWidgetItem *item = table->item(cx,cy);
            if (item!=nullptr) {
                no = QVariant(item->text()).toDouble();
            } else {
                no = QVariant(cxStr).toDouble();
            }

            if (foundSign) {
                if (op==OPERATION::ADD) {
                    result+=no;
                } else if (op==OPERATION::SUB) {
                    result-=no;
                } else if (op==OPERATION::MP) {
                    result*=no;
                } else if (op==OPERATION::DIV) {
                    result/=no;
                }
            } else {
                result = QVariant(no).toDouble();
            }

            cx = cy = no = 0;
            cxStr = "";
            cyStr = "";

            parse = false;
            foundComma = false;
            inBracket = false;
        } else if (c==',') {
            foundComma = true;
        } else {
            if (parse==false) {
                continue;
            }
            if (inBracket) {
                cxStr+=c;
            } else if (foundComma) {
                cyStr+=c;
            } else {
                cxStr+=c;
            }
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
