#pragma once

#include <QToolBar>
#include <QToolButton>

class CellBar : public QToolBar {
    Q_OBJECT
public:
    CellBar();
    ~CellBar();
private:
    QToolButton *cellColor, *merge, *unmerge;
private slots:
    void onBgColorClicked();
    void onFgColorClicked();
    void onMergeClicked();
    void onUnMergeClicked();
};
