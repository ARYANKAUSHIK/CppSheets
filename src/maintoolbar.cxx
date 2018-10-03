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

#include "maintoolbar.hh"
#include "actions/file_actions.hh"
#include "actions/format_actions.hh"
#include "actions/data_actions.hh"

MainToolbar::MainToolbar()
    : newFile(new QToolButton),
      open(new QToolButton),
      save(new QToolButton),
      saveAs(new QToolButton),
      bold(new QToolButton),
      italic(new QToolButton),
      underline(new QToolButton),
      fontCombo(new QFontComboBox),
      fontSize(new QSpinBox),
      cut(new QToolButton),
      copy(new QToolButton),
      paste(new QToolButton)
{
    newFile->setIcon(QPixmap(":/icons/document-new.svg"));
    open->setIcon(QPixmap(":/icons/document-open.svg"));
    save->setIcon(QPixmap(":/icons/document-save.svg"));
    saveAs->setIcon(QPixmap(":/icons/document-save-as.svg"));
    bold->setIcon(QPixmap(":/icons/format-text-bold.svg"));
    italic->setIcon(QPixmap(":/icons/format-text-italic.svg"));
    underline->setIcon(QPixmap(":/icons/format-text-underline.svg"));
    cut->setIcon(QPixmap(":/icons/edit-cut.svg"));
    copy->setIcon(QPixmap(":/icons/edit-copy.svg"));
    paste->setIcon(QPixmap(":/icons/edit-paste.svg"));

    newFile->setToolTip("New Speadsheet");
    open->setToolTip("Open Sheet");
    save->setToolTip("Save Sheet");
    saveAs->setToolTip("Save As");
    bold->setToolTip("Bold");
    italic->setToolTip("Italic");
    underline->setToolTip("Underline");
    cut->setToolTip("Cut Cell Data");
    copy->setToolTip("Copy Cell Data");
    paste->setToolTip("Paste Cell Data");

    fontSize->setMinimum(1);
    fontSize->setMaximum(100);
    fontSize->setValue(12);

    connect(newFile,&QToolButton::clicked,this,&MainToolbar::onNewFileClicked);
    connect(open,&QToolButton::clicked,this,&MainToolbar::onOpenClicked);
    connect(save,&QToolButton::clicked,this,&MainToolbar::onSaveClicked);
    connect(saveAs,&QToolButton::clicked,this,&MainToolbar::onSaveAsClicked);
    connect(bold,&QToolButton::clicked,this,&MainToolbar::onBoldClicked);
    connect(italic,&QToolButton::clicked,this,&MainToolbar::onItalicClicked);
    connect(underline,&QToolButton::clicked,this,&MainToolbar::onUnderlineClicked);
    connect(fontCombo,SIGNAL(currentFontChanged(QFont)),this,SLOT(onFontChanged(QFont)));
    connect(fontSize,SIGNAL(valueChanged(int)),this,SLOT(onFontSizeChanged(int)));
    connect(cut,&QToolButton::clicked,this,&MainToolbar::onCutClicked);
    connect(copy,&QToolButton::clicked,this,&MainToolbar::onCopyClicked);
    connect(paste,&QToolButton::clicked,this,&MainToolbar::onPasteClicked);

    this->addWidget(newFile);
    this->addWidget(open);
    this->addWidget(save);
    this->addWidget(saveAs);
    this->addSeparator();
    this->addWidget(bold);
    this->addWidget(italic);
    this->addWidget(underline);
    this->addSeparator();
    this->addWidget(fontCombo);
    this->addWidget(fontSize);
    this->addSeparator();
    this->addWidget(cut);
    this->addWidget(copy);
    this->addWidget(paste);
}

MainToolbar::~MainToolbar() {
    delete newFile;
    delete open;
    delete save;
    delete saveAs;
    delete bold;
    delete italic;
    delete underline;
    delete fontCombo;
    delete fontSize;
    delete cut;
    delete copy;
    delete paste;
}

void MainToolbar::onNewFileClicked() {
    FileActions::newFile();
}

void MainToolbar::onOpenClicked() {
    FileActions::openFile();
}

void MainToolbar::onSaveClicked() {
    FileActions::saveFile();
}

void MainToolbar::onSaveAsClicked() {
    FileActions::saveFileAs();
}

void MainToolbar::onBoldClicked() {
    FormatActions::bold();
}

void MainToolbar::onItalicClicked() {
    FormatActions::italic();
}

void MainToolbar::onUnderlineClicked() {
    FormatActions::underline();
}

void MainToolbar::onFontChanged(QFont font) {
    FormatActions::setFontFamily(font.family());
}

void MainToolbar::onFontSizeChanged(int val) {
    FormatActions::setFontSize(val);
}

void MainToolbar::onCutClicked() {
    DataActions::load_clipboard(true);
}

void MainToolbar::onCopyClicked() {
    DataActions::load_clipboard(false);
}

void MainToolbar::onPasteClicked() {
    DataActions::paste_data();
}
