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
#include "page_menu.hh"
#include "../tabwidget.hh"
#include "../sheetwidget.hh"

PageMenu::PageMenu() {
    copy = new QAction("Copy",this);
    rename = new QAction("Rename",this);

    connect(copy,&QAction::triggered,this,&PageMenu::onCopyClicked);
    connect(rename,&QAction::triggered,this,&PageMenu::onRenameClicked);

    this->addAction(copy);
    this->addAction(rename);
}

PageMenu::~PageMenu() {
    delete copy;
    delete rename;
}

void PageMenu::onCopyClicked() {
    auto current = TabWidget::currentWidget();
    QString oldPage = current->currentPage();
    current->insertPage();

    auto data = current->data(oldPage);
    auto mathData = current->mathData(oldPage);
    current->setData(data,current->currentTable());
    current->currentTable()->setMathItems(mathData);
}

void PageMenu::onRenameClicked() {
    int current = TabWidget::currentWidget()->currentIndex();
    TabWidget::currentWidget()->renamePage(current);
}
