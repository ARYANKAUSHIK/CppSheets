#pragma once

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QPainter>

QT_CHARTS_USE_NAMESPACE

class BarGraph {
public:
    BarGraph();
    QChartView *generateGraph();
    void addCategory(QString name);
    void addSet(QString name, QList<qreal> contents);
private:
    QBarSeries *series;
    QStringList categories;
};