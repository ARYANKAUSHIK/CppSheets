#include "window.hh"
#include "maintoolbar.hh"
#include "tabwidget.hh"

Window::Window() {
    this->setWindowTitle("CppSheets");
    this->resize(800,600);

    TabWidget *tabs = new TabWidget;
    MainToolbar *toolbar = new MainToolbar;

    this->addToolBar(toolbar);
    this->setCentralWidget(tabs);
}

Window::~Window() {
}
