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
      cut(new QToolButton),
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
    paste->setIcon(QPixmap(":/icons/edit-paste.svg"));

    newFile->setToolTip("New Speadsheet");
    open->setToolTip("Open Sheet");
    save->setToolTip("Save Sheet");
    saveAs->setToolTip("Save As");
    bold->setToolTip("Bold");
    italic->setToolTip("Italic");
    underline->setToolTip("Underline");
    cut->setToolTip("Cut Cell Data");
    paste->setToolTip("Paste Cell Data");

    connect(newFile,&QToolButton::clicked,this,&MainToolbar::onNewFileClicked);
    connect(open,&QToolButton::clicked,this,&MainToolbar::onOpenClicked);
    connect(save,&QToolButton::clicked,this,&MainToolbar::onSaveClicked);
    connect(saveAs,&QToolButton::clicked,this,&MainToolbar::onSaveAsClicked);
    connect(bold,&QToolButton::clicked,this,&MainToolbar::onBoldClicked);
    connect(italic,&QToolButton::clicked,this,&MainToolbar::onItalicClicked);
    connect(underline,&QToolButton::clicked,this,&MainToolbar::onUnderlineClicked);
    connect(cut,&QToolButton::clicked,this,&MainToolbar::onCutClicked);
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
    this->addWidget(cut);
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
    delete cut;
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

void MainToolbar::onCutClicked() {
    DataActions::load_clipboard(true);
}

void MainToolbar::onPasteClicked() {
    DataActions::paste_data();
}
