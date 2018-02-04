#include "math.hh"

void Math::updateMath(QVector<MathItem> mathItems, TableWidget *table) {
    for (int i = 0; i<mathItems.size(); i++) {
        int x = mathItems.at(i).x;
        int y = mathItems.at(i).y;
        QString equ = mathItems.at(i).equation;

        QString math = "";
        QString dir = "";
        QString range1 = "";
        QString range2 = "";
        bool range1B = true;
        ParseType type = ParseType::TYPE;

        for (int j = 1; j<equ.size(); j++) {
            if (equ.at(j)=='(') {
                type = ParseType::DIR;
                continue;
            } else if (equ.at(j)==')') {
                continue;
            } else if (equ.at(j)=='[') {
                type = ParseType::RANGE;
            } else if (equ.at(j)==']') {
                if (range1B) {
                    range1B = false;
                }
                continue;
            } else {
                switch (type) {
                case ParseType::TYPE: math+=equ.at(j); break;
                case ParseType::DIR: dir+=equ.at(j); break;
                case ParseType::RANGE: {
                    if (range1B) {
                        range1+=equ.at(j);
                    } else {
                        range2+=equ.at(j);
                    }
                } break;
                }
            }
        }

        int r1 = QVariant(range1).toInt();
        int r2 = QVariant(range2).toInt();
        QStringList cellNumbers;

        for (int j = r1; j<=r2; j++) {
            if (dir=="x") {
                QTableWidgetItem *item = table->item(j,y);
                if (item==nullptr) {
                    continue;
                }
                cellNumbers.push_back(item->text());
            } else {
                QTableWidgetItem *item = table->item(x,j);
                if (item==nullptr) {
                    continue;
                }
                cellNumbers.push_back(item->text());
            }
        }

        double result = 0;
        int s = 0;
        if ((math=="sub")||(math=="div")) {
            if (cellNumbers.size()!=0) {
                result = QVariant(cellNumbers.at(0)).toDouble();
                s = 1;
            }
        }
        for (int j = s; j<cellNumbers.size(); j++) {
            double current = QVariant(cellNumbers.at(j)).toDouble();
            if (math=="sum") {
                result+=current;
            } else if (math=="sub") {
                result-=current;
            } else if (math=="mp") {
                result*=current;
            } else if (math=="div") {
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
}
