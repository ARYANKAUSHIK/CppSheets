#include <QIcon>
#include <QFileDialog>
#include <QFileInfo>

#include "maintoolbar.hh"
#include "tabwidget.hh"
#include "parser.hh"

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
    TabWidget::addNewTab();
}

void MainToolbar::onOpenClicked() {
    QFileDialog dialog;
    dialog.setWindowTitle("Open File");
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    if (dialog.exec()) {
        if (dialog.selectedFiles().size()==0) {
            return;
        }
        QString selected = dialog.selectedFiles().at(0);
        if (TabWidget::currentWidget()->isUntitled()&&TabWidget::currentWidget()->isSaved()) {
            TabWidget::currentWidget()->setFile(selected);
            TabWidget::currentWidget()->loadFile();
            TabWidget::setCurrentTitle(QFileInfo(selected).fileName());
        } else {
            TabWidget::addNewTab(selected);
        }
    }
}

void MainToolbar::onSaveClicked() {
    if (TabWidget::currentWidget()->isUntitled()) {
        //Save as
        return;
    }
    auto pages = TabWidget::currentWidget()->allPages();
    QString filePath = TabWidget::currentWidget()->file();
    for (int i = 0; i<pages.size(); i++) {
        auto data = TabWidget::currentWidget()->data(pages.at(i));
        if (!Parser::pageExists(filePath,pages.at(i))) {
            Parser::createPage(filePath,pages.at(i));
        }
        Parser::setData(filePath,pages.at(i),data);
    }
}
