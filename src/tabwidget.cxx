// This file is part of CppSheets.
//
// Copyright 2018 Patrick Flynn <patrick_dev2000@outlook.com>
//
// CppSheets is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CppSheets is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CppSheets. If not, see <https://www.gnu.org/licenses/>.
#include <QFileInfo>
#include <QMessageBox>

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

    connect(tabs,SIGNAL(tabCloseRequested(int)),this,SLOT(onTabCloseRequested(int)));
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

SheetWidget *TabWidget::widgetAt(int index) {
    SheetWidget *widget = static_cast<SheetWidget *>(tabs->widget(index));
    return widget;
}

void TabWidget::setCurrentTitle(QString title) {
    tabs->setTabText(tabs->currentIndex(),title);
}

void TabWidget::onTabCloseRequested(int index) {
    if (tabs->count()==1) {
        addNewTab();
    }
    auto widget = widgetAt(index);
    if (widget->isSaved()) {
        delete widget;
    } else {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Warning);
        msg.setText("This file has not been saved.\n"
                    "Do you wish to close it?");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = msg.exec();
        if (ret==QMessageBox::Yes) {
            delete widget;
        }
    }
}

void TabWidget::onCurrentChanged() {
    Window::setCurrentPath(currentWidget()->file());
    Window::setCurrentSaved(currentWidget()->isSaved());
}
