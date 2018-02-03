#include "tablewidget.hh"

TableWidget::TableWidget() {
    this->setColumnCount(1000);
    this->setRowCount(1000);
    this->setStyleSheet("QTableWidget::item:selected { background-color:white; color:black; "
                        "border-color: blue; border-style:solid; border-width:2px; }");

    connect(this,&TableWidget::cellChanged,this,&TableWidget::onCellChanged);
}

void TableWidget::onCellChanged() {
    emit cellModified();
}
