#pragma once

#include <QVector>

#include "parser.hh"
#include "tablewidget.hh"

enum OPERATION {
    ADD,
    SUB,
    MP,
    DIV
};

struct Cell {
    int x;
    int y;
};

class Math {
public:
    static void updateMath(QVector<MathItem> mathItems, TableWidget *table);
    static void applyBulkFormula(MathItem mathItem, TableWidget *table);
    static void applyColumnFormula(MathItem mathItem, TableWidget *table);
};
