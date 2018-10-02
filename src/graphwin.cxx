#include <bargraph.hh>
#include <QDialog>
#include <QList>
#include <QPainter>
#include <QOpenGLWidget>
#include <iostream>

#include "graphwin.hh"
#include "tabwidget.hh"
#include "formula/formula_utils.hh"

GraphWin::GraphWin()
    : parent(new QFrame),
      addSetWidget(new QFrame),
      categoryWidget(new QFrame),
      parentLayout(new QVBoxLayout),
      setLayout(new QHBoxLayout),
      categoryLayout(new QHBoxLayout),
      name(new QLineEdit),
      range(new QLineEdit),
      category(new QLineEdit),
      set(new QPushButton("Add Set")),
      addCategory(new QPushButton("Add Category")),
      showGraph(new QPushButton("Show Graph")),
      tabs(new QTabWidget),
      sets(new QTreeWidget),
      categories(new QListWidget)
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

    connect(set,&QPushButton::clicked,this,&GraphWin::onAddSet);

    //The categories widget
    categoryWidget->setLayout(categoryLayout);
    parentLayout->addWidget(categoryWidget);

    categoryLayout->addWidget(new QLabel("Category Name: "));
    categoryLayout->addWidget(category);
    categoryLayout->addWidget(addCategory);

    connect(addCategory,&QPushButton::clicked,this,&GraphWin::onAddCategory);

    //The tab pane
    parentLayout->addWidget(tabs);

    //The sets list
    sets->setHeaderLabels(QStringList() << "Name" << "Range");
    tabs->addTab(sets,"Sets");

    //The categories list
    tabs->addTab(categories,"Categories");

    //This button generates the graph
    parentLayout->addWidget(showGraph);

    connect(showGraph,&QPushButton::clicked,this,&GraphWin::onShowGraph);
}

void GraphWin::onAddSet() {
    QTreeWidgetItem *item = new QTreeWidgetItem(sets);
    item->setText(0,name->text());
    item->setText(1,range->text());
}

void GraphWin::onAddCategory() {
    categories->addItem(category->text());
}

void GraphWin::onShowGraph() {
    BarGraph *graph = new BarGraph;

    //Get the categories
    for (int i = 0; i<categories->count(); i++) {
        auto current = categories->item(i);
        graph->addCategory(current->text());
    }

    //Get the sets
    for (int i = 0; i<sets->topLevelItemCount(); i++) {
        auto item = sets->topLevelItem(i);

        QList<qreal> data;
        auto contents = FormulaUtils::rangeContents(item->text(1),
                                            TabWidget::currentWidget()->currentTable());

        for (QString str : contents) {
            data.append(QVariant(str).toReal());
        }

        graph->addSet(item->text(0),data);
    }

    auto chart = graph->generateGraph();

    QFrame *chartParent = new QFrame;
    QVBoxLayout *chartParentLayout = new QVBoxLayout;
    chartParentLayout->setContentsMargins(0,0,0,0);
    chartParentLayout->addWidget(chart);
    chartParent->setLayout(chartParentLayout);

    QDialog dialog;
    dialog.resize(550,400);
    QVBoxLayout *dLayout = new QVBoxLayout;
    dialog.setLayout(dLayout);
    dLayout->addWidget(chartParent);
    dialog.exec();

    QPixmap p = chart->grab();
    QOpenGLWidget *glWidget  = chart->findChild<QOpenGLWidget*>();
    if(glWidget){
        QPainter painter(&p);
        QPoint d = glWidget->mapToGlobal(QPoint())-chart->mapToGlobal(QPoint());
        painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
        painter.drawImage(d, glWidget->grabFramebuffer());
        painter.end();
    }
    p.save("test.png", "PNG");
}
