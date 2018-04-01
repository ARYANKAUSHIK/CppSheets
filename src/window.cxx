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

#include "window.hh"
#include "ribbon.hh"
#include "tabwidget.hh"

StatusBar *Window::statusbar;

Window::Window() {
    this->setWindowTitle("CppSheets");
    this->setWindowIcon(QPixmap(":/icons/kspread.png"));
    this->resize(800,600);

    TabWidget *tabs = new TabWidget;
    Ribbon *ribbon = new Ribbon;

    QWidget *centerWidget = new QWidget;
    QVBoxLayout *centerLayout = new QVBoxLayout;
    centerLayout->setContentsMargins(0,0,0,0);
    centerWidget->setLayout(centerLayout);
    this->setCentralWidget(centerWidget);

    centerLayout->addWidget(ribbon,0,Qt::AlignTop);
    centerLayout->addWidget(tabs);

    statusbar = new StatusBar;
    this->setStatusBar(statusbar);
}

Window::~Window() {
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
