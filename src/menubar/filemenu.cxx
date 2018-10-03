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
