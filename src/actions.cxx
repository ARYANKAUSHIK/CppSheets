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

void Actions::saveFile() {
    if (TabWidget::currentWidget()->isUntitled()) {
        saveFileAs();
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

void Actions::saveFileAs() {

}
