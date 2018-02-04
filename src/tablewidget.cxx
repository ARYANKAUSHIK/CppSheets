#include <iostream>

#include "tablewidget.hh"

enum ParseType {
    TYPE,
    DIR,
    RANGE
};

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
    mathItems.push_back(item);
}

void TableWidget::updateMath() {
    for (int i = 0; i<mathItems.size(); i++) {
        int x = mathItems.at(i).x;
        int y = mathItems.at(i).y;
        QString equ = mathItems.at(i).equation;

        //Equation parser
        //We will move this if it works
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
                QTableWidgetItem *item = this->item(j,y);
                if (item==nullptr) {
                    continue;
                }
                cellNumbers.push_back(item->text());
            } else {
                QTableWidgetItem *item = this->item(x,j);
                if (item==nullptr) {
                    continue;
                }
                cellNumbers.push_back(item->text());
            }
        }

        int result;
        if ((math=="sum")||(math=="sub")) {
            result = 0;
        } else {
            result = 1;
        }
        for (int j = 0; j<cellNumbers.size(); j++) {
            int current = QVariant(cellNumbers.at(j)).toInt();
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
        QTableWidgetItem *item = this->item(x,y);
        if (item==nullptr) {
            item = new QTableWidgetItem;
        }
        item->setText(strResult);
        this->setItem(x,y,item);
    }
}

void TableWidget::onCellChanged() {
    emit cellModified();
}

void TableWidget::onItemChanged(QTableWidgetItem *item) {
    updateMath();
}
