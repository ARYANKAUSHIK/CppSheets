#include <QTableWidgetItem>
#include <iostream>

#include "sheetwidget.hh"
#include "tablewidget.hh"
#include "parser.hh"

SheetWidget::SheetWidget(QString path)
    : layout(new QVBoxLayout),
      currentData(new QLineEdit),
      tabs(new QTabWidget)
{
    filePath = path;

    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    tabs->setTabPosition(QTabWidget::South);
    if (path=="untitled") {
        TableWidget *table = new TableWidget;
        connect(table,&TableWidget::cellModified,this,&SheetWidget::onCellChanged);
        connect(table,SIGNAL(currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)),this,SLOT(onCellLocoChanged(QTableWidgetItem*,QTableWidgetItem*)));
        tabs->addTab(table,"page 1");
    }

    connect(currentData,&QLineEdit::returnPressed,this,&SheetWidget::onCurrentDataEnterPressed);

    layout->addWidget(currentData,0,Qt::AlignTop);
    layout->addWidget(tabs);

    addTab = new QToolButton;
    addTab->setText("+");
    connect(addTab,&QToolButton::clicked,this,&SheetWidget::onAddTabClicked);
    tabs->setCornerWidget(addTab,Qt::TopLeftCorner);
}

SheetWidget::~SheetWidget() {
}

void SheetWidget::loadFile() {
    for (int i = 0; i<tabs->count(); i++) {
        delete tabs->widget(i);
    }

    auto pageList = Parser::pages(filePath);
    for (int i = 0; i<pageList.size(); i++) {
        TableWidget *table = new TableWidget;
        connect(table,&TableWidget::cellModified,this,&SheetWidget::onCellChanged);
        connect(table,SIGNAL(currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)),this,SLOT(onCellLocoChanged(QTableWidgetItem*,QTableWidgetItem*)));
        table->setMathItems(Parser::allMathItems(filePath,pageList.at(i)));
        tabs->addTab(table,pageList.at(i));

        auto itemList = Parser::allItems(filePath,pageList.at(i));
        for (int j = 0; j<itemList.size(); j++) {
            int x = itemList.at(j).x;
            int y = itemList.at(j).y;
            QString text = itemList.at(j).data;

            QTableWidgetItem *item = new QTableWidgetItem(text);
            if (!itemList.at(j).tooltip.isNull()) {
                item->setToolTip(itemList.at(j).tooltip);
            }
            item->setBackgroundColor(itemList.at(j).bgColor);
            item->setTextColor(itemList.at(j).fgColor);
            table->setItem(x,y,item);
        }
    }
}

QStringList SheetWidget::allPages() {
    QStringList items;
    for (int i = 0; i<tabs->count(); i++) {
        items.push_back(tabs->tabText(i));
    }
    return items;
}

QVector<SheetItem> SheetWidget::data(QString page) {
    QVector<SheetItem> items;

    int index = 0;
    for (int i = 0; i<tabs->count(); i++) {
        if (tabs->tabText(i)==page) {
            index = i;
            break;
        }
    }

    TableWidget *table = static_cast<TableWidget *>(tabs->widget(index));

    for (int x = 0; x<table->columnCount(); x++) {
        for (int y = 0; y<table->rowCount(); y++) {
            QTableWidgetItem *item = table->item(x,y);
            if (item==nullptr) {
                continue;
            }

            SheetItem sitem;
            sitem.x = x;
            sitem.y = y;
            sitem.data = item->text();
            QString bgRole = item->data(Qt::BackgroundRole).toString();
            if (bgRole.isEmpty()) {
                sitem.bgColor = Qt::white;
            } else {
                sitem.bgColor = item->background().color();
            }
            sitem.fgColor = item->foreground().color();

            if (!item->toolTip().isNull()) {
                sitem.tooltip = item->toolTip();
            }

            items.push_back(sitem);
        }
    }

    return items;
}

void SheetWidget::setFile(QString path) {
    filePath = path;
}

QString SheetWidget::file() {
    return filePath;
}

bool SheetWidget::isUntitled() {
    if (filePath=="untitled") {
        return true;
    } else {
        return false;
    }
}

void SheetWidget::setSaved(bool s) {
    saved = s;
}

bool SheetWidget::isSaved() {
    return saved;
}

TableWidget *SheetWidget::currentTable() {
    TableWidget *table = static_cast<TableWidget *>(tabs->currentWidget());
    return table;
}

QTableWidgetItem *SheetWidget::currentCell() {
    QTableWidgetItem *item = currentTable()->currentItem();
    int x = currentTable()->currentRow();
    int y = currentTable()->currentColumn();
    if (item==nullptr) {
        item = new QTableWidgetItem;
    }
    currentTable()->setItem(x,y,item);
    return item;
}

void SheetWidget::onCellChanged() {
    saved = false;
}

void SheetWidget::onCellLocoChanged(QTableWidgetItem *current, QTableWidgetItem *last) {
    if (current==nullptr) {
        currentData->setText("");
    } else {
        currentData->setText(current->text());
    }
}

void SheetWidget::onCurrentDataEnterPressed() {
    QTableWidgetItem *item = currentCell();
    QString data = currentData->text();
    if (data.startsWith("=")) {
        MathItem mitem;
        mitem.x = item->row();
        mitem.y = item->column();
        mitem.equation = data;
        currentTable()->addMathItem(mitem);
        currentTable()->updateMath();
    } else {
        item->setText(currentData->text());
    }

    int row = item->row()+1;
    int col = item->column();
    currentTable()->setCurrentCell(row,col);

    currentData->setText("");
}

void SheetWidget::onAddTabClicked() {
    int count = tabs->count();
    TableWidget *table = new TableWidget;
    connect(table,&TableWidget::cellModified,this,&SheetWidget::onCellChanged);
    tabs->addTab(new TableWidget(),"page "+QVariant(tabs->count()+1).toString());
    tabs->setCurrentIndex(count);
    saved = false;
}
