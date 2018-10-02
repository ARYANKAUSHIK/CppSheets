#include "graph_menu.hh"
#include "../window.hh"

GraphMenu::GraphMenu() {
    this->setTitle("Graph");

    showGraph = new QAction("Show Graph Designer",this);

    connect(showGraph,&QAction::triggered,this,&GraphMenu::onShowGraph);

    this->addAction(showGraph);
}

GraphMenu::~GraphMenu() {
    delete showGraph;
}

void GraphMenu::onShowGraph() {
    Window::showGraphWin();
}
