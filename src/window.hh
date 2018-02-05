#pragma once

#include <QMainWindow>

#include "statusbar.hh"

class Window : public QMainWindow {
    Q_OBJECT
public:
    Window();
    ~Window();
    static void setCurrentPath(QString path);
    static void setCurrentSaved(bool saved);
private:
    static StatusBar *statusbar;
};
