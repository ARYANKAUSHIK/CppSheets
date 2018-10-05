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
#include <QOpenGLWidget>
#include <QFileDialog>

#include "graph_dialog.hh"

GraphDialog::GraphDialog(QChartView *graph)
    : layout(new QVBoxLayout),
      toolbar(new QToolBar)
{
    chart = graph;

    this->setWindowTitle("Graph Display");
    this->resize(700,500);
    this->setLayout(layout);

    //Add our toolbar
    save = new QToolButton;
    fullscreen = new QToolButton;
    exit = new QToolButton;

    save->setIcon(QPixmap(":/icons/image.svg"));
    fullscreen->setIcon(QPixmap(":/icons/view-fullscreen.svg"));
    exit->setIcon(QPixmap(":/icons/close.svg"));

    connect(save,&QToolButton::clicked,this,&GraphDialog::onSaveClicked);
    connect(fullscreen,&QToolButton::clicked,this,&GraphDialog::onFullscreenClicked);
    connect(exit,&QToolButton::clicked,this,&GraphDialog::close);

    toolbar->addWidget(save);
    toolbar->addWidget(fullscreen);
    toolbar->addWidget(exit);

    //Add everything to the window
    layout->addWidget(toolbar,0,Qt::AlignTop);
    layout->addWidget(graph);
}

GraphDialog::~GraphDialog() {
}

void GraphDialog::onSaveClicked() {
    QPixmap p = chart->grab();
    QOpenGLWidget *glWidget  = chart->findChild<QOpenGLWidget*>();
    if(glWidget){
        QPainter painter(&p);
        QPoint d = glWidget->mapToGlobal(QPoint())-chart->mapToGlobal(QPoint());
        painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
        painter.drawImage(d, glWidget->grabFramebuffer());
        painter.end();
    }

    QFileDialog chooser;
    chooser.setWindowTitle("Save As Image");
    chooser.setAcceptMode(QFileDialog::AcceptSave);
    chooser.setDirectory(QDir::home());

    if (!chooser.exec() || chooser.selectedFiles().length()==0) {
        return;
    }

    QString path = chooser.selectedFiles().at(0);
    p.save(path,"PNG");
}

void GraphDialog::onFullscreenClicked() {
    if (this->isFullScreen()) {
        this->showNormal();
    } else {
        this->showFullScreen();
    }
}
