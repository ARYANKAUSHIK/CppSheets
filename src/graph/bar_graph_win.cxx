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
#include <bargraph.hh>
#include <QDialog>
#include <QList>
#include <QPainter>
#include <QOpenGLWidget>
#include <iostream>

#include "bar_graph_win.hh"
#include "../tabwidget.hh"
#include "../formula/formula_utils.hh"
#include "../dialogs/graph_dialog.hh"

BarGraphWin::BarGraphWin()
    : parent(new QFrame),
      nameWidget(new QFrame),
      addSetWidget(new QFrame),
      categoryWidget(new QFrame),
      parentLayout(new QVBoxLayout),
      nameLayout(new QHBoxLayout),
      setLayout(new QHBoxLayout),
      categoryLayout(new QHBoxLayout),
      graphName(new QLineEdit),
      name(new QLineEdit),
      range(new QLineEdit),
      category(new QLineEdit),
      set(new QPushButton("Add Set")),
      addCategory(new QPushButton("Add Category")),
      showGraph(new QPushButton("Show Graph")),
      tabs(new QTabWidget),
      sets(new QTreeWidget),
      categories(new QListWidget),
      saveGraph(new QCheckBox)
{
    this->setWindowTitle("Graph");

    //Set up the base widget
    parentLayout->setContentsMargins(0,0,0,0);
    parent->setLayout(parentLayout);
    this->setWidget(parent);

    //The graph name widget
    nameWidget->setLayout(nameLayout);
    parentLayout->addWidget(nameWidget);

    nameLayout->addWidget(new QLabel("Graph name: "));
    nameLayout->addWidget(graphName);

    //The graph set widget
    addSetWidget->setLayout(setLayout);
    parentLayout->addWidget(addSetWidget);

    setLayout->addWidget(new QLabel("Name: "));
    setLayout->addWidget(name);
    setLayout->addWidget(new QLabel("Range: "));
    setLayout->addWidget(range);
    setLayout->addWidget(set);

    connect(set,&QPushButton::clicked,this,&BarGraphWin::onAddSet);

    //The categories widget
    categoryWidget->setLayout(categoryLayout);
    parentLayout->addWidget(categoryWidget);

    categoryLayout->addWidget(new QLabel("Category Name: "));
    categoryLayout->addWidget(category);
    categoryLayout->addWidget(addCategory);

    connect(addCategory,&QPushButton::clicked,this,&BarGraphWin::onAddCategory);

    //The tab pane
    parentLayout->addWidget(tabs);

    //The sets list
    sets->setHeaderLabels(QStringList() << "Name" << "Range");
    tabs->addTab(sets,"Sets");

    //The categories list
    tabs->addTab(categories,"Categories");

    //The checkbox for saving a graph
    saveGraph->setText("Save Graph Data");
    parentLayout->addWidget(saveGraph);

    //This button generates the graph
    parentLayout->addWidget(showGraph);

    connect(showGraph,&QPushButton::clicked,this,&BarGraphWin::onShowGraph);
}

//Loads saved graph data for viewing
void BarGraphWin::loadGraphData(GraphItem item) {
    graphName->setText(item.name);

    categories->clear();
    categories->addItems(item.categories);

    sets->clear();
    for (GraphSet s : item.sets) {
        QTreeWidgetItem *item = new QTreeWidgetItem(sets);
        item->setText(0,s.name);
        item->setText(1,s.range);
    }
}

void BarGraphWin::writeGraphData() {
    GraphItem item;
    item.name = graphName->text();
    item.type = GraphType::BAR;
    item.categories = getCategories();

    for (int i = 0; i<sets->topLevelItemCount(); i++) {
        auto current = sets->topLevelItem(i);

        GraphSet set;
        set.name = current->text(0);
        set.range = current->text(1);
        item.sets << set;
    }

    auto table = TabWidget::currentWidget()->currentTable();
    table->addGraphItem(item);
}

//This returns a list of the user's categories
QStringList BarGraphWin::getCategories() {
    QStringList ret;

    for (int i = 0; i<categories->count(); i++) {
        auto current = categories->item(i);
        ret << current->text();
    }

    return ret;
}

void BarGraphWin::onAddSet() {
    QTreeWidgetItem *item = new QTreeWidgetItem(sets);
    item->setText(0,name->text());
    item->setText(1,range->text());
}

void BarGraphWin::onAddCategory() {
    categories->addItem(category->text());
}

void BarGraphWin::onShowGraph() {
    if (saveGraph->isChecked()) {
        writeGraphData();
    }

    BarGraph *graph = new BarGraph;
    graph->setName(graphName->text());

    //Get the categories
    auto cl = getCategories();
    for (QString ln : cl) {
        graph->addCategory(ln);
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

    GraphDialog dialog(chart);
    dialog.exec();

    /*QPixmap p = chart->grab();
    QOpenGLWidget *glWidget  = chart->findChild<QOpenGLWidget*>();
    if(glWidget){
        QPainter painter(&p);
        QPoint d = glWidget->mapToGlobal(QPoint())-chart->mapToGlobal(QPoint());
        painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
        painter.drawImage(d, glWidget->grabFramebuffer());
        painter.end();
    }
    p.save("test.png", "PNG");*/
}
