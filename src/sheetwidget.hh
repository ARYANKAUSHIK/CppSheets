#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTabWidget>
#include <QString>
#include <QToolButton>
#include <QVector>
#include <QStringList>
#include <QTableWidgetItem>

#include "parser.hh"
#include "tablewidget.hh"

class SheetWidget : public QWidget {
    Q_OBJECT
public:
    SheetWidget(QString path);
    ~SheetWidget();
    void loadFile();
    QStringList allPages();
    QVector<SheetItem> data(QString page);
    void setFile(QString path);
    QString file();
    bool isUntitled();
    void setSaved(bool s);
    bool isSaved();
    TableWidget *currentTable();
    QTableWidgetItem *currentCell();
private:
    QVBoxLayout *layout;
    QLineEdit *currentData;
    QTabWidget *tabs;
    QToolButton *addTab;
    QString filePath;
    bool saved = true;
private slots:
    void onCellChanged();
    void onCellLocoChanged(QTableWidgetItem *current, QTableWidgetItem *last);
    void onCurrentDataEnterPressed();
    void onAddTabClicked();
    void onTabDoubleClick(int index);
};
