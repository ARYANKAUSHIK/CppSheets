#include "tablewidget.hh"

TableWidget::TableWidget() {
    this->setColumnCount(1000);
    this->setRowCount(1000);

    connect(this,&TableWidget::cellChanged,this,&TableWidget::onCellChanged);
}

void TableWidget::onCellChanged() {
    emit cellModified();
}
