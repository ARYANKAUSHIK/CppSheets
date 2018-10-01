#include "bargraph.hh"

BarGraph::BarGraph() {
    series = new QBarSeries();
}

void BarGraph::addCategory(QString name) {
    categories << name;
}

void BarGraph::addSet(QString name, QList<qreal> contents) {
    QBarSet *set = new QBarSet(name);
    set->append(contents);
    series->append(set);
}

QChartView *BarGraph::generateGraph() {
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("My Bar Graph");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}
