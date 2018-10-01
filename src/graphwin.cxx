#include "graphwin.hh"

GraphWin::GraphWin()
    : parent(new QFrame),
      addSetWidget(new QFrame),
      parentLayout(new QVBoxLayout),
      setLayout(new QHBoxLayout),
      name(new QLineEdit),
      range(new QLineEdit),
      set(new QPushButton("Add Set")),
      showGraph(new QPushButton("Show Graph")),
      sets(new QListWidget)
{
    this->setWindowTitle("Graph");

    //Set up the base widget
    parentLayout->setContentsMargins(0,0,0,0);
    parent->setLayout(parentLayout);
    this->setWidget(parent);

    //The graph set widget
    addSetWidget->setLayout(setLayout);
    parentLayout->addWidget(addSetWidget);

    setLayout->addWidget(new QLabel("Name: "));
    setLayout->addWidget(name);
    setLayout->addWidget(new QLabel("Range: "));
    setLayout->addWidget(range);
    setLayout->addWidget(set);

    //The sets list
    parentLayout->addWidget(sets);

    //This button generates the graph
    parentLayout->addWidget(showGraph);
}
