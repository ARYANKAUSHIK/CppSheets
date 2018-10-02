#pragma once

#include <QDockWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QTreeWidget>
#include <QListWidget>

class GraphWin : public QDockWidget {
    Q_OBJECT
public:
    GraphWin();
private:
    QFrame *parent, *addSetWidget, *categoryWidget;
    QVBoxLayout *parentLayout;
    QHBoxLayout *setLayout, *categoryLayout;
    QLineEdit *name, *range, *category;
    QPushButton *set, *addCategory, *showGraph;
    QTabWidget *tabs;
    QTreeWidget *sets;
    QListWidget *categories;
private slots:
    void onAddSet();
    void onAddCategory();
    void onShowGraph();
};
