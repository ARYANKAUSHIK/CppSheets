#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTabWidget>

#include "sheetwidget.hh"

class TabWidget : public QWidget {
    Q_OBJECT
public:
    TabWidget();
    ~TabWidget();
    static void addNewTab();
    static void addNewTab(QString file);
    static SheetWidget *currentWidget();
    static void setCurrentTitle(QString title);
private:
    QVBoxLayout *layout;
    static QTabWidget *tabs;
private slots:
    void onCurrentChanged();
};
