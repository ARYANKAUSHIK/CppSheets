#pragma once

#include <QToolBar>
#include <QToolButton>

class MainToolbar : public QToolBar {
    Q_OBJECT
public:
    MainToolbar();
    ~MainToolbar();
private:
    QToolButton *newFile, *open, *save;
private slots:
    void onNewFileClicked();
    void onOpenClicked();
    void onSaveClicked();
};
