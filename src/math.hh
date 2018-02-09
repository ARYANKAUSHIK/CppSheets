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

class Math {
public:
    static void updateMath(QVector<MathItem> mathItems, TableWidget *table);
};
