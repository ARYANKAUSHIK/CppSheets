#pragma once

#include <QDockWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>

class GraphWin : public QDockWidget {
    Q_OBJECT
public:
    GraphWin();
private:
    QFrame *parent, *addSetWidget;
    QVBoxLayout *parentLayout;
    QHBoxLayout *setLayout;
    QLineEdit *name, *range;
    QPushButton *set, *showGraph;
    QListWidget *sets;
};
