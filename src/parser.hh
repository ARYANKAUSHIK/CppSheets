#pragma once

#include <QString>
#include <QStringList>
#include <QVector>
#include <QColor>

#include "tinyxml2.h"

using namespace tinyxml2;

struct SheetItem {
    int x;
    int y;
    QString data;
    QColor bgColor;
    QColor fgColor;
    QString tooltip;
};

class Parser {
public:
	static QStringList pages(QString file);
    static QVector<SheetItem> allItems(QString file, QString page);
    static void createPage(QString file, QString page);
    static bool pageExists(QString file, QString pageName);
    static void removePage(QString file, QString page);
    static void setData(QString file, QString page, QVector<SheetItem> items);
    static XMLElement *getPageElement(XMLElement *root, QString title);
};
