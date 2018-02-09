#include <iostream>

#include "math.hh"

void Math::updateMath(QVector<MathItem> mathItems, TableWidget *table) {
    for (int i = 0; i<mathItems.size(); i++) {
        int x = mathItems.at(i).x;
        int y = mathItems.at(i).y;
        QString equ = mathItems.at(i).equation;

        QString newEqu = equ.remove(0,1);
        bool foundSign = false;
        bool parse = false;
        bool foundComma = false;
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
            } else if (c=='(') {
                parse = true;
            } else if (c==')') {
                cx = QVariant(cxStr).toInt();
                cy = QVariant(cyStr).toInt();
                cx--;
                cy--;

                QTableWidgetItem *item = table->item(cx,cy);
                if (item!=nullptr) {
                    std::cout << QString(item->text()).toStdString() << std::endl;
                    if (foundSign) {
                        no = QVariant(item->text()).toDouble();
                        std::cout << "No: " << no << std::endl;
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
                        result = QVariant(item->text()).toDouble();
                        std::cout << "Result: " << result << std::endl;
                    }
                }

                cx = cy = no = 0;
                cxStr = "";
                cyStr = "";

                parse = false;
                foundComma = false;
            } else if (c==',') {
                foundComma = true;
            } else {
                if (parse==false) {
                    continue;
                }
                if (foundComma) {
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
}
