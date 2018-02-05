#pragma once

#include <QStatusBar>
#include <QLabel>

class StatusBar : public QStatusBar {
    Q_OBJECT
public:
    StatusBar();
    ~StatusBar();
    void setPathLabel(QString label);
    void setSavedLabel(bool saved);
private:
    QLabel *pathLabel;
    QLabel *savedLabel;
};
