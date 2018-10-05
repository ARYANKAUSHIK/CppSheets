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
#include <QVBoxLayout>
#include <QPixmap>
#include <QMessageBox>
#include <QMenuBar>

#include "window.hh"
#include "maintoolbar.hh"
#include "tabwidget.hh"

StatusBar *Window::statusbar;
BarGraphWin *Window::graphWin;

Window::Window() {
    this->setWindowTitle("CppSheets");
    this->setWindowIcon(QPixmap(":/icons/sheets.svg"));
    this->resize(1000,800);

    TabWidget *tabs = new TabWidget;
    MainToolbar *toolbar = new MainToolbar;

    QWidget *centerWidget = new QWidget;
    QVBoxLayout *centerLayout = new QVBoxLayout;
    centerLayout->setContentsMargins(0,0,0,0);
    centerWidget->setLayout(centerLayout);
    this->setCentralWidget(centerWidget);

    this->addToolBar(Qt::TopToolBarArea,toolbar);
    centerLayout->addWidget(tabs);

    filemenu = new FileMenu;
    formatMenu = new FormatMenu;
    cellMenu = new CellMenu;
    graphMenu = new GraphMenu;
    helpMenu = new HelpMenu;

    this->menuBar()->addMenu(filemenu);
    this->menuBar()->addMenu(formatMenu);
    this->menuBar()->addMenu(cellMenu);
    this->menuBar()->addMenu(graphMenu);
    this->menuBar()->addMenu(helpMenu);

    statusbar = new StatusBar;
    this->setStatusBar(statusbar);

    graphWin = new BarGraphWin;
    graphWin->hide();
    this->addDockWidget(Qt::RightDockWidgetArea,graphWin);
}

Window::~Window() {
    delete filemenu;
    delete formatMenu;
    delete cellMenu;
    delete helpMenu;
}

void Window::setCurrentPath(QString path) {
    statusbar->setPathLabel(path);
}

void Window::setCurrentSaved(bool saved) {
    statusbar->setSavedLabel(saved);
}

void Window::showGraphWin() {
    if (graphWin->isVisible()) {
        graphWin->hide();
    } else {
        graphWin->show();
    }
}

bool Window::checkSave() {
    int count = TabWidget::tabs->count();
    for (int i = 0; i<count; i++) {
        SheetWidget *sheet = TabWidget::widgetAt(i);
        if (!sheet->isSaved()) {
            QMessageBox msg;
            msg.setWindowTitle("Warning");
            msg.setText("You have unsaved files!\nDo you wish to exit?");
            msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msg.setIcon(QMessageBox::Warning);
            int ret = msg.exec();
            if (ret==QMessageBox::Yes) {
                return true;
            } else {
                return false;
            }
        }
    }
    return true;
}

void Window::closeEvent(QCloseEvent *event) {
    if (checkSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}
