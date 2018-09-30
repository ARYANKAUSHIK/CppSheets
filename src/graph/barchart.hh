#ifndef BARCHART_HH
#define BARCHART_HH

#include <QDockWidget>

namespace Ui {
class BarChart;
}

class BarChart : public QDockWidget
{
    Q_OBJECT

public:
    explicit BarChart(QWidget *parent = nullptr);
    ~BarChart();

private:
    Ui::BarChart *ui;
};

#endif // BARCHART_HH
