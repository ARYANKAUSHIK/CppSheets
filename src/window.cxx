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
#include <QVBoxLayout>
#include <QPixmap>
#include <QMessageBox>
#include <QMenuBar>

#include "window.hh"
#include "maintoolbar.hh"
#include "tabwidget.hh"
#include "graphwin.hh"

StatusBar *Window::statusbar;

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
    helpMenu = new HelpMenu;

    this->menuBar()->addMenu(filemenu);
    this->menuBar()->addMenu(formatMenu);
    this->menuBar()->addMenu(cellMenu);
    this->menuBar()->addMenu(helpMenu);

    statusbar = new StatusBar;
    this->setStatusBar(statusbar);

    GraphWin *graphWin = new GraphWin;
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
