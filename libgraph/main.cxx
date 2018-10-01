#include <QApplication>
#include <QMainWindow>

#include "bargraph.hh"

int main(int argc, char **argv) {
    QApplication app(argc,argv);

    QMainWindow *win = new QMainWindow;
    win->setWindowTitle("Graph Test");
    win->resize(700,550);

    BarGraph *bg = new BarGraph;

    bg->addCategory("Q1");
    bg->addCategory("Q2");
    bg->addCategory("Q3");
    bg->addCategory("Q4");

    QList<qreal> numbers;
    numbers << 1 << 2 << 3 << 4;

    bg->addSet("Danny",numbers);

    numbers.clear();
    numbers << 3 << 7 << 9 << 1;
    bg->addSet("Dave",numbers);

    numbers.clear();
    numbers << 1 << 8 << 2 << 3;
    bg->addSet("Bob",numbers);

    auto *graph = bg->generateGraph();
    win->setCentralWidget(graph);

    win->show();

    return app.exec();
}