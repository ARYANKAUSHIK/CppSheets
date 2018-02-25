#include <QVBoxLayout>
#include <QPixmap>

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
