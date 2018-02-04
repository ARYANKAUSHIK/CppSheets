#pragma once

#include <QToolBar>
#include <QToolButton>

class HomeBar : public QToolBar {
    Q_OBJECT
public:
    HomeBar();
    ~HomeBar();
private:
    QToolButton *cellColor;
private slots:
    void onBgColorClicked();
    void onFgColorClicked();
};
