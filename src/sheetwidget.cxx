#include <QTableWidgetItem>
#include <iostream>

#include "sheetwidget.hh"
#include "tablewidget.hh"
#include "parser.hh"

SheetWidget::SheetWidget(QString path)
    : layout(new QVBoxLayout),
      tabs(new QTabWidget)
{
    filePath = path;

    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    tabs->setTabPosition(QTabWidget::South);
    if (path=="untitled") {
        TableWidget *table = new TableWidget;
        connect(table,&TableWidget::cellModified,this,&SheetWidget::onCellChanged);
        tabs->addTab(new TableWidget(),"page 1");
    }
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

void SheetWidget::onCellChanged() {
    saved = false;
}

void SheetWidget::onAddTabClicked() {
    int count = tabs->count();
    TableWidget *table = new TableWidget;
    connect(table,&TableWidget::cellModified,this,&SheetWidget::onCellChanged);
    tabs->addTab(new TableWidget(),"page "+QVariant(tabs->count()+1).toString());
    tabs->setCurrentIndex(count);
    saved = false;
}
