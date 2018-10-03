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
#include <QPixmap>
#include <QKeySequence>
#include <QFontDialog>
#include <QTableWidgetItem>

#include "format_menu.hh"
#include "../actions/format_actions.hh"
#include "../tabwidget.hh"

FormatMenu::FormatMenu() {
    this->setTitle("Format");

    bold = new QAction("Bold",this);
    italic = new QAction("Italic",this);
    underline = new QAction("Underline",this);
    border = new QAction("Set Border",this);
    setFont = new QAction("Set Font",this);
    
    colorMenu = new QMenu;
    colorMenu->setTitle("Color");
    bg = new QAction("Background",colorMenu);
    fg = new QAction("Text",colorMenu);
    colorMenu->addAction(bg);
    colorMenu->addAction(fg);

    bold->setIcon(QPixmap(":/icons/format-text-bold.svg"));
    italic->setIcon(QPixmap(":/icons/format-text-italic.svg"));
    underline->setIcon(QPixmap(":/icons/format-text-underline.svg"));

    bold->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_B));
    italic->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_I));
    underline->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_U));

    connect(bold,&QAction::triggered,this,&FormatMenu::onBoldClicked);
    connect(italic,&QAction::triggered,this,&FormatMenu::onItalicClicked);
    connect(underline,&QAction::triggered,this,&FormatMenu::onUnderlineClicked);
    connect(bg,&QAction::triggered,this,&FormatMenu::onBgColorClicked);
    connect(fg,&QAction::triggered,this,&FormatMenu::onFgColorClicked);
    connect(border,&QAction::triggered,this,&FormatMenu::onBorderClicked);
    connect(setFont,&QAction::triggered,this,&FormatMenu::onSetFontClicked);

    this->addAction(bold);
    this->addAction(italic);
    this->addAction(underline);
    this->addMenu(colorMenu);
    this->addAction(border);
    this->addAction(setFont);
}

FormatMenu::~FormatMenu() {
    delete bold;
    delete italic;
    delete underline;
    delete colorMenu;
    delete border;
    delete setFont;
}

void FormatMenu::onBoldClicked() {
    FormatActions::bold();
}

void FormatMenu::onItalicClicked() {
    FormatActions::italic();
}

void FormatMenu::onUnderlineClicked() {
    FormatActions::underline();
}

void FormatMenu::onBgColorClicked() {
    FormatActions::bgColor();
}

void FormatMenu::onFgColorClicked() {
    FormatActions::fgColor();
}

void FormatMenu::onBorderClicked() {
    FormatActions::dspBorderDialog();
}

void FormatMenu::onSetFontClicked() {
    QFontDialog dialog;

    if (!dialog.exec()) {
        return;
    }

    QFont font = dialog.selectedFont();
    auto item = TabWidget::currentWidget()->currentCell();
    item->setFont(font);
}

