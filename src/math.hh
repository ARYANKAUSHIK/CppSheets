#pragma once

#include <QVector>

#include "parser.hh"
#include "tablewidget.hh"

enum ParseType {
    TYPE,
    DIR,
    RANGE
};

class Math {
public:
    static void updateMath(QVector<MathItem> mathItems, TableWidget *table);
};
