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
#include <QFileDialog>
#include <QFileInfo>

#include "actions.hh"
#include "tabwidget.hh"
#include "parser/xml_parser.hh"
#include "sheetwidget.hh"

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

void Actions::bold() {
    SheetWidget *sheet = TabWidget::currentWidget();
    QTableWidgetItem *item = sheet->currentCell();
    QFont font = item->font();
    if (font.bold()) {
        font.setBold(false);
    } else {
        font.setBold(true);
    }
    item->setFont(font);
}

void Actions::italic() {
    SheetWidget *sheet = TabWidget::currentWidget();
    QTableWidgetItem *item = sheet->currentCell();
    QFont font = item->font();
    if (font.italic()) {
        font.setItalic(false);
    } else {
        font.setItalic(true);
    }
    item->setFont(font);
}

void Actions::underline() {
    SheetWidget *sheet = TabWidget::currentWidget();
    QTableWidgetItem *item = sheet->currentCell();
    QFont font = item->font();
    if (font.underline()) {
        font.setUnderline(false);
    } else {
        font.setUnderline(true);
    }
    item->setFont(font);
}
