#include <QTableWidgetItem>
#include <QInputDialog>
#include <QMessageBox>
#include <iostream>

#include "sheetwidget.hh"
#include "tablewidget.hh"
#include "parser.hh"
#include "window.hh"

SheetWidget::SheetWidget(QString path)
    : layout(new QVBoxLayout),
      currentData(new QLineEdit),
      tabs(new QTabWidget)
{
    filePath = path;

    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    tabs->setTabPosition(QTabWidget::South);
    tabs->setTabsClosable(true);

    if (path=="untitled") {
        TableWidget *table = new TableWidget;
        connect(table,&TableWidget::cellModified,this,&SheetWidget::onCellChanged);
        connect(table,SIGNAL(currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)),this,SLOT(onCellLocoChanged(QTableWidgetItem*,QTableWidgetItem*)));
        tabs->addTab(table,"page 1");
    }

    connect(currentData,&QLineEdit::returnPressed,this,&SheetWidget::onCurrentDataEnterPressed);
    connect(tabs,SIGNAL(tabBarDoubleClicked(int)),this,SLOT(onTabDoubleClick(int)));
    connect(tabs,SIGNAL(tabCloseRequested(int)),this,SLOT(onTabClose(int)));

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

            table->setColumnWidth(y,itemList.at(j).colWidth);
            table->setRowHeight(x,itemList.at(j).rowWidth);

            table->setSpan(x,y,itemList.at(j).spanx,itemList.at(j).spany);
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
            sitem.colWidth = table->columnWidth(y);
            sitem.rowWidth = table->rowHeight(x);
            sitem.spanx = table->rowSpan(x,y);
            sitem.spany = table->columnSpan(x,y);
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

QVector<MathItem> SheetWidget::mathData(QString page) {
    QVector<MathItem> items;

    for (int i = 0; i<tabs->count(); i++ ) {
        if (tabs->tabText(i)==page) {
            TableWidget *table = static_cast<TableWidget *>(tabs->widget(i));
            items = table->allMathItems();
            break;
        }
    }

    return items;
}

void SheetWidget::setFile(QString path) {
    filePath = path;
    Window::setCurrentPath(path);
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
    Window::setCurrentSaved(s);
}

bool SheetWidget::isSaved() {
    return saved;
}

void SheetWidget::mergeSelected() {
    QVector<int> cols, rows;

    auto list = currentTable()->currentSelectedItems();
    for (int i = 0; i<list.size(); i++) {
        cols.push_back(list.at(i).column());
        rows.push_back(list.at(i).row());
    }

    int sx = rows.at(0);
    int sy = cols.at(0);
    int lx = 0;
    int ly = 0;

    //Smallest y value
    for (int i = 0; i<cols.size(); i++) {
        if (cols.at(i)<sy) {
            sy = cols.at(i);
        }
    }

    //Smallest x value
    for (int i = 0; i<rows.size(); i++) {
        if (rows.at(i)<sx) {
            sx = rows.at(i);
        }
    }

    //Largest y value
    for (int i = 0; i<cols.size(); i++) {
        if (cols.at(i)>ly) {
            ly = cols.at(i);
        }
    }

    //Largest x value
    for (int i = 0; i<rows.size(); i++) {
        if (rows.at(i)>lx) {
            lx = rows.at(i);
        }
    }

    lx++;
    ly++;

    int ex = lx-sx;
    int ey = ly-sy;

    currentTable()->setSpan(sx,sy,ex,ey);
}

void SheetWidget::unMergeSelected() {
    QTableWidgetItem *item = currentCell();
    int x = item->row();
    int y = item->column();

    currentTable()->setSpan(x,y,1,1);
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

void SheetWidget::addNewTab(int no) {
    int count = tabs->count();
    TableWidget *table = new TableWidget;
    connect(table,&TableWidget::cellModified,this,&SheetWidget::onCellChanged);
    connect(table,SIGNAL(currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)),this,SLOT(onCellLocoChanged(QTableWidgetItem*,QTableWidgetItem*)));
    tabs->addTab(new TableWidget(),"page "+QVariant(no).toString());
    tabs->setCurrentIndex(count);
}

void SheetWidget::onCellChanged() {
    saved = false;
    Window::setCurrentSaved(false);
}

void SheetWidget::onCellLocoChanged(QTableWidgetItem *current, QTableWidgetItem *last) {
    if (current==nullptr) {
        currentData->setText("");
    } else {
        if (currentTable()->isMath(currentTable()->currentRow(),currentTable()->currentColumn())) {
             currentData->setText(currentTable()->formula(currentTable()->currentRow(),currentTable()->currentColumn()));
        } else {
            currentData->setText(current->text());
        }
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
    } else if (data=="-{\\") {
        item->setToolTip("");
    } else if (data.startsWith("-{")) {
        item->setToolTip(data.replace("-{",""));
    } else {
        item->setText(currentData->text());
    }

    int x = item->row()+1;
    int y = item->column();
    currentTable()->setCurrentCell(x,y);
}

void SheetWidget::onAddTabClicked() {
    addNewTab(tabs->count()+1);
    saved = false;
    Window::setCurrentSaved(false);
}

void SheetWidget::onTabDoubleClick(int index) {
    if (index==-1) {
        return;
    }

    QInputDialog dialog;
    dialog.setWindowTitle("Rename Page");
    dialog.setLabelText("Enter name for your page:");
    dialog.setTextValue(tabs->tabText(index));

    if (!dialog.exec()) {
        return;
    }

    tabs->setTabText(index,dialog.textValue());

    saved = false;
    Window::setCurrentSaved(false);
}

void SheetWidget::onTabClose(int index) {
    QMessageBox msg;
    msg.setWindowTitle("Confirm");
    msg.setText("This will delete the page you have selected.\n"
                "Are you sure you wish to continue?");
    msg.setIcon(QMessageBox::Warning);
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int ret = msg.exec();

    if (ret==QMessageBox::No) {
        return;
    }

    if (tabs->count()==1) {
        this->addNewTab(1);
    }

    QString title = tabs->tabText(index);
    delete tabs->widget(index);
    Parser::removePage(filePath,title);

    saved = false;
    Window::setCurrentSaved(false);
}

