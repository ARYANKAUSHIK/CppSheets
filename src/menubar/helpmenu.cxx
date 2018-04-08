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
#include <QPixmap>
#include <QApplication>
#include <QMessageBox>

#include "helpmenu.hh"

HelpMenu::HelpMenu() {
    this->setTitle("Help");

    about = new QAction("About",this);
    aboutQt = new QAction("About Qt",this);

    about->setIcon(QPixmap(":/icons/help-about.png"));

    connect(about,&QAction::triggered,this,&HelpMenu::onAboutClicked);
    connect(aboutQt,&QAction::triggered,qApp,&QApplication::aboutQt);

    this->addAction(about);
    this->addAction(aboutQt);
}

HelpMenu::~HelpMenu() {
    delete about;
    delete aboutQt;
}

void HelpMenu::onAboutClicked() {
    QMessageBox msg;
    msg.setIcon(QMessageBox::Information);
    msg.setWindowTitle("About CppSheets");
    msg.setText("CppSheets: A simple spreadsheet application.\n"
                "Written by Patrick; see <https://github.com/patrickf2000/CppSheets>\n\n"
                "Credits:\n"
                "xlnt <https://github.com/tfussell/xlnt>\n"
                "tinyxml2 <https://github.com/leethomason/tinyxml2>");
    msg.exec();
}
