#include <QIcon>

#include "maintoolbar.hh"
#include "actions.hh"

MainToolbar::MainToolbar()
    : newFile(new QToolButton),
      open(new QToolButton),
      save(new QToolButton)
{
    newFile->setIcon(QIcon::fromTheme("document-new"));
    open->setIcon(QIcon::fromTheme("document-open"));
    save->setIcon(QIcon::fromTheme("document-save"));

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
