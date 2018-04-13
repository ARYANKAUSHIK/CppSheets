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
#include <QMenu>
#include <QAction>

#include "cellbar.hh"
#include "actions/format_actions.hh"
#include "tabwidget.hh"

CellBar::CellBar()
    : cellColor(new QToolButton),
      merge(new QToolButton),
      unmerge(new QToolButton),
      borderTest(new QToolButton)
{
    QMenu *colorMenu = new QMenu;
    QAction *bg = new QAction("Background",colorMenu);
    QAction *fg = new QAction("Text",colorMenu);
    colorMenu->addAction(bg);
    colorMenu->addAction(fg);

    cellColor->setPopupMode(QToolButton::InstantPopup);
    cellColor->setMenu(colorMenu);

    cellColor->setText("Color");
    merge->setText("Merge Cells");
    unmerge->setText("Unmerge Cells");
    borderTest->setText("Border Test");

    this->addWidget(cellColor);
    this->addWidget(merge);
    this->addWidget(unmerge);
    this->addWidget(borderTest);

    connect(bg,&QAction::triggered,this,&CellBar::onBgColorClicked);
    connect(fg,&QAction::triggered,this,&CellBar::onFgColorClicked);
    connect(merge,&QToolButton::clicked,this,&CellBar::onMergeClicked);
    connect(unmerge,&QToolButton::clicked,this,&CellBar::onUnMergeClicked);
    connect(borderTest,&QToolButton::clicked,this,&CellBar::onBorderTestClicked);
}

CellBar::~CellBar() {
    delete cellColor;
    delete merge;
    delete borderTest;
}

void CellBar::onBgColorClicked() {
    FormatActions::bgColor();
}

void CellBar::onFgColorClicked() {
    FormatActions::fgColor();
}

void CellBar::onMergeClicked() {
    FormatActions::merge();
}

void CellBar::onUnMergeClicked() {
    FormatActions::unMerge();
}

void CellBar::onBorderTestClicked() {
    TabWidget::currentWidget()->currentCell()->setData(Qt::ForegroundRole,QVariant("please_test"));
}
