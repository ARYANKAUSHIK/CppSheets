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
#include <QKeySequence>
#include <QPixmap>
#include <QApplication>

#include "filemenu.hh"
#include "../actions/file_actions.hh"
#include "../window.hh"

FileMenu::FileMenu() {
    this->setTitle("File");

    newFile = new QAction("New",this);
    open = new QAction("Open",this);
    save = new QAction("Save",this);
    saveAs = new QAction("Save As",this);
    quit = new QAction("Quit",this);

    newFile->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_N));
    open->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_O));
    save->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_S));
    saveAs->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_S));
    quit->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Q));

    newFile->setIcon(QPixmap(":/icons/document-new.svg"));
    open->setIcon(QPixmap(":/icons/document-open.svg"));
    save->setIcon(QPixmap(":/icons/document-save.svg"));
    saveAs->setIcon(QPixmap(":/icons/document-save-as.svg"));
    quit->setIcon(QPixmap(":/icons/application-exit.svg"));

    connect(newFile,&QAction::triggered,this,&FileMenu::onNewFileClicked);
    connect(open,&QAction::triggered,this,&FileMenu::onOpenClicked);
    connect(save,&QAction::triggered,this,&FileMenu::onSaveClicked);
    connect(saveAs,&QAction::triggered,this,&FileMenu::onSaveAsClicked);
    connect(quit,&QAction::triggered,this,&FileMenu::onQuitClicked);

    this->addAction(newFile);
    this->addAction(open);
    this->addAction(save);
    this->addAction(saveAs);
    this->addAction(quit);
}

FileMenu::~FileMenu() {
    delete newFile;
    delete open;
    delete save;
    delete saveAs;
    delete quit;
}

void FileMenu::onNewFileClicked() {
    FileActions::newFile();
}

void FileMenu::onOpenClicked() {
    FileActions::openFile();
}

void FileMenu::onSaveClicked() {
    FileActions::saveFile();
}

void FileMenu::onSaveAsClicked() {
    FileActions::saveFileAs();
}

void FileMenu::onQuitClicked() {
    if (Window::checkSave()) {
        qApp->exit(0);
    }
}
