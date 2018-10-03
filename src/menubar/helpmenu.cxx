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
#include <QPixmap>
#include <QApplication>
#include <QMessageBox>

#include "helpmenu.hh"

HelpMenu::HelpMenu() {
    this->setTitle("Help");

    about = new QAction("About",this);
    aboutQt = new QAction("About Qt",this);

    about->setIcon(QPixmap(":/icons/help-about.svg"));

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
