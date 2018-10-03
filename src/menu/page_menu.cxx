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
