// Copyright 2018 Patrick Flynn
//
// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, 
//	this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this 
//	list of conditions and the following disclaimer in the documentation and/or 
//	other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may 
//	be used to endorse or promote products derived from this software 
//	without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

SheetWidget *TabWidget::widgetAt(int index) {
    SheetWidget *widget = static_cast<SheetWidget *>(tabs->widget(index));
    return widget;
}

void TabWidget::setCurrentTitle(QString title) {
    tabs->setTabText(tabs->currentIndex(),title);
}

void TabWidget::onCurrentChanged() {
    Window::setCurrentPath(currentWidget()->file());
    Window::setCurrentSaved(currentWidget()->isSaved());
}
