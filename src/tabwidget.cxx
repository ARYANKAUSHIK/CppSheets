#include <QFileInfo>

#include "tabwidget.hh"
#include "window.hh"

QTabWidget *TabWidget::tabs;

TabWidget::TabWidget()
    : layout(new QVBoxLayout)
{
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    tabs = new QTabWidget;
    tabs->setTabBarAutoHide(true);
    tabs->setTabsClosable(true);
    tabs->setMovable(true);

    tabs->addTab(new SheetWidget("untitled"),"untitled");
    layout->addWidget(tabs);

    connect(tabs,&QTabWidget::currentChanged,this,&TabWidget::onCurrentChanged);
}

TabWidget::~TabWidget() {
    delete layout;
}

void TabWidget::addNewTab() {
    int count = tabs->count();
    tabs->addTab(new SheetWidget("untitled"),"untitled");
    tabs->setCurrentIndex(count);

    Window::setCurrentPath("untitled");
    Window::setCurrentSaved(true);
}

void TabWidget::addNewTab(QString file) {
    int count = tabs->count();
    SheetWidget *sheet = new SheetWidget(file);
    sheet->loadFile();
    tabs->addTab(sheet,QFileInfo(file).fileName());
    tabs->setCurrentIndex(count);

    Window::setCurrentPath(file);
    Window::setCurrentSaved(true);
}

SheetWidget *TabWidget::currentWidget() {
    SheetWidget *widget = static_cast<SheetWidget *>(tabs->currentWidget());
    return widget;
}

void TabWidget::setCurrentTitle(QString title) {
    tabs->setTabText(tabs->currentIndex(),title);
}

void TabWidget::onCurrentChanged() {
    Window::setCurrentPath(currentWidget()->file());
    Window::setCurrentSaved(currentWidget()->isSaved());
}
