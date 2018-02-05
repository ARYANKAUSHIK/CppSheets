#pragma once

#include <QTabWidget>

#include "maintoolbar.hh"
#include "cellbar.hh"

class Ribbon : public QTabWidget {
    Q_OBJECT
public:
    Ribbon();
    ~Ribbon();
private:
    MainToolbar *fileBar;
    CellBar *cellBar;
};
