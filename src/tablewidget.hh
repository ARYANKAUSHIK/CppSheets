#pragma once

#include <QTableWidget>

class TableWidget : public QTableWidget {
    Q_OBJECT
public:
    TableWidget();
private slots:
    void onCellChanged();
signals:
    void cellModified();
};
