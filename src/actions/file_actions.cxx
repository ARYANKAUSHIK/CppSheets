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
#include <QFileDialog>
#include <QFileInfo>

#include "file_actions.hh"
#include "../tabwidget.hh"
#include "../parser/parser.hh"
#include "../sheetwidget.hh"

void FileActions::newFile() {
    TabWidget::addNewTab();
}

void FileActions::openFile() {
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

void FileActions::saveFile() {
    if (TabWidget::currentWidget()->isUntitled()) {
        saveFileAs();
        return;
    }
    auto pages = TabWidget::currentWidget()->allPages();
    QString filePath = TabWidget::currentWidget()->file();
    for (int i = 0; i<pages.size(); i++) {
        auto data = TabWidget::currentWidget()->data(pages.at(i));
        auto mathData = TabWidget::currentWidget()->mathData(pages.at(i));
        auto graphData = TabWidget::currentWidget()->graphData(pages.at(i));

        if (!Parser::pageExists(filePath,pages.at(i))) {
            Parser::createPage(filePath,pages.at(i));
        }

        Parser::setData(filePath,pages.at(i),data);
        Parser::setMathData(filePath,pages.at(i),mathData);
        Parser::setGraphData(filePath,pages.at(i),graphData);
    }

    auto filePages = Parser::pages(filePath);
    for (int i = 0; i<filePages.size(); i++) {
        if (!pages.contains(filePages.at(i))) {
            Parser::removePage(filePath,filePages.at(i));
        }
    }

    TabWidget::currentWidget()->setSaved(true);
}

void FileActions::saveFileAs() {
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
