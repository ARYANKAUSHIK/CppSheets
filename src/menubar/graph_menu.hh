#pragma once

#include <QMenu>
#include <QAction>

class GraphMenu : public QMenu {
    Q_OBJECT
public:
    GraphMenu();
    ~GraphMenu();
private:
    QAction *showGraph;
private slots:
    void onShowGraph();
};
