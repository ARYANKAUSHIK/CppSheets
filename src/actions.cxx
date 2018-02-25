#include <QFileDialog>
#include <QFileInfo>

#include "actions.hh"
#include "tabwidget.hh"
#include "parser.hh"

void Actions::newFile() {
    TabWidget::addNewTab();
}

void Actions::openFile() {
    QFileDialog dialog;
    dialog.setWindowTitle("Open File");
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setDirectory(QDir::homePath());
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
        TabWidget::currentWidget()->setSaved(true);
    }
}

void Actions::saveFile() {
    if (TabWidget::currentWidget()->isUntitled()) {
        saveFileAs();
        return;
    }
    auto pages = TabWidget::currentWidget()->allPages();
    QString filePath = TabWidget::currentWidget()->file();
    for (int i = 0; i<pages.size(); i++) {
        auto data = TabWidget::currentWidget()->data(pages.at(i));
        auto mathData = TabWidget::currentWidget()->mathData(pages.at(i));
        if (!Parser::pageExists(filePath,pages.at(i))) {
            Parser::createPage(filePath,pages.at(i));
        }
        Parser::setData(filePath,pages.at(i),data);
        Parser::setMathData(filePath,pages.at(i),mathData);
    }

    auto filePages = Parser::pages(filePath);
    for (int i = 0; i<filePages.size(); i++) {
        if (!pages.contains(filePages.at(i))) {
            Parser::removePage(filePath,filePages.at(i));
        }
    }

    TabWidget::currentWidget()->setSaved(true);
}

void Actions::saveFileAs() {
    QFileDialog dialog;
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setWindowTitle("Save As");
    if (dialog.exec()) {
        if (dialog.selectedFiles().size()==0) {
            return;
        }
        QString selected = dialog.selectedFiles().at(0);
        TabWidget::currentWidget()->setFile(selected);
        TabWidget::setCurrentTitle(QFileInfo(selected).fileName());
        Parser::createFile(selected);

        saveFile();
    }
}
