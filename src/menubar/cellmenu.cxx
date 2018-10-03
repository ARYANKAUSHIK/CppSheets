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
#include "cellmenu.hh"
#include "../actions/format_actions.hh"
#include "../tabwidget.hh"

CellMenu::CellMenu() {
    this->setTitle("Cells");
    
    merge = new QAction("Merge Cells",this);
    unMerge = new QAction("Unmerge Cells",this);
    insCol = new QAction("Insert Column",this);
    insRow = new QAction("Insert Row",this);
    
    connect(merge,&QAction::triggered,this,&CellMenu::onMergeClicked);
    connect(unMerge,&QAction::triggered,this,&CellMenu::onUnMergeClicked);
    connect(insCol,&QAction::triggered,this,&CellMenu::onInsertCol);
    connect(insRow,&QAction::triggered,this,&CellMenu::onInsertRow);
    
    this->addAction(merge);
    this->addAction(unMerge);
    this->addAction(insCol);
    this->addAction(insRow);
}

CellMenu::~CellMenu() {
    delete merge;
    delete unMerge;
    delete insCol;
    delete insRow;
}

void CellMenu::onMergeClicked() {
    FormatActions::merge();
}

void CellMenu::onUnMergeClicked() {
    FormatActions::unMerge();
}

void CellMenu::onInsertCol() {
    FormatActions::insertCol();
}

void CellMenu::onInsertRow() {
    FormatActions::insertRow();
}

