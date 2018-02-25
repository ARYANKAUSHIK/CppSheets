#include <QPixmap>

#include "maintoolbar.hh"
#include "actions.hh"

MainToolbar::MainToolbar()
    : newFile(new QToolButton),
      open(new QToolButton),
      save(new QToolButton)
{
    newFile->setIcon(QPixmap(":/icons/document-new.png"));
    open->setIcon(QPixmap(":/icons/document-open.png"));
    save->setIcon(QPixmap(":/icons/document-save.png"));

    newFile->setToolTip("New Speadsheet");
    open->setToolTip("Open Sheet");
    save->setToolTip("Save Sheet");

    connect(newFile,&QToolButton::clicked,this,&MainToolbar::onNewFileClicked);
    connect(open,&QToolButton::clicked,this,&MainToolbar::onOpenClicked);
    connect(save,&QToolButton::clicked,this,&MainToolbar::onSaveClicked);

    this->addWidget(newFile);
    this->addWidget(open);
    this->addWidget(save);
}

MainToolbar::~MainToolbar() {
    delete newFile;
    delete open;
    delete save;
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
