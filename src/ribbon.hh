#pragma once

#include <QTabWidget>

#include "maintoolbar.hh"

class Ribbon : public QTabWidget {
    Q_OBJECT
public:
    Ribbon();
    ~Ribbon();
private:
    MainToolbar *fileBar;
};
