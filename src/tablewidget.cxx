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
    mathItems.push_back(item);
}

void TableWidget::updateMath() {
    Math::updateMath(mathItems,this);
}

void TableWidget::onCellChanged() {
    emit cellModified();
}

void TableWidget::onItemChanged(QTableWidgetItem *item) {
    updateMath();
}
