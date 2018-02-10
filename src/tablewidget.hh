#pragma once

#include <QTableWidget>
#include <QVector>
#include <QTableWidgetItem>
#include <QModelIndexList>
#include <QKeyEvent>

#include "parser.hh"

class TableWidget : public QTableWidget {
    Q_OBJECT
public:
    TableWidget();
    void setMathItems(QVector<MathItem> items);
    void addMathItem(MathItem item);
    QVector<MathItem> allMathItems();
    void updateMath();
    bool isMath(int row, int col);
    QString formula(int row, int col);
    QModelIndexList currentSelectedItems();
private:
    void keyPressEvent(QKeyEvent *event);
private:
    QVector<MathItem> mathItems;
private slots:
    void onCellChanged();
    void onItemChanged(QTableWidgetItem *item);
signals:
    void cellModified();
};
