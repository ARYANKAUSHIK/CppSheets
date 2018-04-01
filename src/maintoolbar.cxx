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
#include "actions.hh"

MainToolbar::MainToolbar()
    : newFile(new QToolButton),
      open(new QToolButton),
      save(new QToolButton),
      saveAs(new QToolButton),
      bold(new QToolButton)
{
    newFile->setIcon(QPixmap(":/icons/document-new.png"));
    open->setIcon(QPixmap(":/icons/document-open.png"));
    save->setIcon(QPixmap(":/icons/document-save.png"));
    saveAs->setIcon(QPixmap(":/icons/document-save-as.png"));
    bold->setIcon(QPixmap(":/icons/format-text-bold.png"));

    newFile->setToolTip("New Speadsheet");
    open->setToolTip("Open Sheet");
    save->setToolTip("Save Sheet");
    saveAs->setToolTip("Save As");
    bold->setToolTip("Bold");

    connect(newFile,&QToolButton::clicked,this,&MainToolbar::onNewFileClicked);
    connect(open,&QToolButton::clicked,this,&MainToolbar::onOpenClicked);
    connect(save,&QToolButton::clicked,this,&MainToolbar::onSaveClicked);
    connect(saveAs,&QToolButton::clicked,this,&MainToolbar::onSaveAsClicked);
    connect(bold,&QToolButton::clicked,this,&MainToolbar::onBoldClicked);

    this->addWidget(newFile);
    this->addWidget(open);
    this->addWidget(save);
    this->addWidget(saveAs);
    this->addSeparator();
    this->addWidget(bold);
}

MainToolbar::~MainToolbar() {
    delete newFile;
    delete open;
    delete save;
    delete saveAs;
    delete bold;
}

void MainToolbar::onNewFileClicked() {
    Actions::newFile();
}

void MainToolbar::onOpenClicked() {
    Actions::openFile();
}

void MainToolbar::onSaveClicked() {
    Actions::saveFile();
}

void MainToolbar::onSaveAsClicked() {
    Actions::saveFileAs();
}

void MainToolbar::onBoldClicked() {
    Actions::bold();
}
