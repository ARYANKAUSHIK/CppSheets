#include <QPixmap>

#include "maintoolbar.hh"
#include "actions.hh"

MainToolbar::MainToolbar()
    : newFile(new QToolButton),
      open(new QToolButton),
      save(new QToolButton),
      saveAs(new QToolButton)
{
    newFile->setIcon(QPixmap(":/icons/document-new.png"));
    open->setIcon(QPixmap(":/icons/document-open.png"));
    save->setIcon(QPixmap(":/icons/document-save.png"));
    saveAs->setIcon(QPixmap(":/icons/document-save-as.png"));

    newFile->setToolTip("New Speadsheet");
    open->setToolTip("Open Sheet");
    save->setToolTip("Save Sheet");
    saveAs->setToolTip("Save As");

    connect(newFile,&QToolButton::clicked,this,&MainToolbar::onNewFileClicked);
    connect(open,&QToolButton::clicked,this,&MainToolbar::onOpenClicked);
    connect(save,&QToolButton::clicked,this,&MainToolbar::onSaveClicked);
    connect(saveAs,&QToolButton::clicked,this,&MainToolbar::onSaveAsClicked);

    this->addWidget(newFile);
    this->addWidget(open);
    this->addWidget(save);
    this->addWidget(saveAs);
}

MainToolbar::~MainToolbar() {
    delete newFile;
    delete open;
    delete save;
    delete saveAs;
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
