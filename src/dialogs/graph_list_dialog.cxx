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
#include "graph_list_dialog.hh"
#include "../tabwidget.hh"
#include "../tablewidget.hh"
#include "../window.hh"

GraphListDialog::GraphListDialog()
    : layout(new QVBoxLayout),
      graphs(new QListWidget)
{
    this->setWindowTitle("Saved Graphs");
    this->resize(600,400);

    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    //The list widget-> Displays graphs
    layout->addWidget(graphs);

    auto table = TabWidget::currentWidget()->currentTable();
    auto gList = table->allGraphItems();

    for (GraphItem item : gList) {
        graphs->addItem(item.name);
    }

    connect(graphs,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,SLOT(onDoubleClick(QListWidgetItem *)));
}

GraphListDialog::~GraphListDialog() {
}

void GraphListDialog::onDoubleClick(QListWidgetItem *item) {
    QString name = item->text();

    auto list = TabWidget::currentWidget()->currentTable()->allGraphItems();
    for (GraphItem item : list) {
        if (item.name==name) {
            if (!Window::graphWin->isVisible()) {
                Window::graphWin->show();
            }

            Window::graphWin->loadGraphData(item);
        }
    }

    this->close();
}
