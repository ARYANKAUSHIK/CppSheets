#include "barchart.hh"
#include "ui_barchart.h"

BarChart::BarChart(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::BarChart)
{
    ui->setupUi(this);
}

BarChart::~BarChart()
{
    delete ui;
}
