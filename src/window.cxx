#include <QVBoxLayout>

#include "window.hh"
#include "ribbon.hh"
#include "tabwidget.hh"

Window::Window() {
    this->setWindowTitle("CppSheets");
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
}

Window::~Window() {
}
