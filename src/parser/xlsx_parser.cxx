// This file is part of CppSheets.
//
// Copyright 2018 Patrick Flynn <patrick_dev2000@outlook.com>
//
// CppSheets is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CppSheets is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CppSheets. If not, see <https://www.gnu.org/licenses/>.
#include <xlnt/xlnt.hpp>
#include <iostream>
#include <QTableWidget>

#include "xlsx_parser.hh"
#include "../tabwidget.hh"

void XlsxParser::createFile(QString filePath) {
	std::cout << "Excel" << std::endl;
}

QStringList XlsxParser::pages(QString file) {
	QStringList pages;

    xlnt::workbook wb;
    wb.load(file.toStdString());
    int no = wb.sheet_count();

    for (int i = 0; i<no; i++) {
        std::string strTitle = wb.sheet_by_index(i).title();
        QString str = QString::fromStdString(strTitle);
        pages.push_back(str);
    }

	return pages;
}

bool XlsxParser::pageExists(QString file, QString pageName) {
    bool found = false;

    xlnt::workbook wb;
    wb.load(file.toStdString());
    int no = wb.sheet_count();

    for (int i = 0; i<no; i++) {
        std::string strTitle = wb.sheet_by_index(i).title();
        QString str = QString::fromStdString(strTitle);
        if (str==pageName) {
            found = true;
            break;
        }
    }

    return found;
}

QVector<SheetItem> XlsxParser::allItems(QString file, QString page) {
	QVector<SheetItem> items;

    xlnt::workbook wb;
    wb.load(file.toStdString());
    if (!pageExists(file,page)) {
        return items;
    }

    auto sheet = wb.sheet_by_title(page.toStdString());
    int c = 0;
    int r = 0;
    for (auto row : sheet.rows(false)) {
        c = 0;
        for (auto cell : row) {
            SheetItem item;
            item.x = r;
            item.y = c;
            item.bgColor = Qt::white;
            item.fgColor = Qt::black;
            item.spanx = 1;
            item.spany = 1;

            try {
                item.data = QString::fromStdString(cell.to_string());
                item.colWidth = cell.width();
                item.rowWidth = cell.height();
            } catch (xlnt::exception &e) {
                std::cout << e.what() << std::endl;
            }

            try {
                QFont font;
                font.setBold(cell.font().bold());
                font.setItalic(cell.font().italic());
                font.setUnderline(cell.font().underlined());
                item.font = font;
            } catch (xlnt::exception &e) {
                std::cout << e.what() << std::endl;
            }

            try {
                std::string bgColor = "#"+cell.format().fill().pattern_fill()
                        .background().get().rgb().hex_string();
                item.bgColor = QColor(QString::fromStdString(bgColor));
            } catch (xlnt::exception &e) {
                std::cout << e.what() << std::endl;
            }

            try {
                std::string fgColor = "#"+cell.font().color().rgb().hex_string();
                item.fgColor = QColor(QString::fromStdString(fgColor));
            } catch (xlnt::exception &e) {
                std::cout << e.what() << std::endl;
            }

            items.push_back(item);
            c++;
        }
        r++;
    }

	return items;
}

QVector<MathItem> XlsxParser::allMathItems(QString file, QString page) {
	QVector<MathItem> items;

    xlnt::workbook wb;
    wb.load(file.toStdString());
    if (!pageExists(file,page)) {
        return items;
    }

    auto sheet = wb.sheet_by_title(page.toStdString());
    int c = 0;
    int r = 0;
    for (auto row : sheet.rows()) {
        c = 0;
        for (auto cell : row) {
            if (cell.has_formula()) {
                MathItem item;
                item.equation = "="+QString::fromStdString(cell.formula());
                item.x = r;
                item.y = c;
                items.push_back(item);
            }
            c++;
        }
        r++;
    }

	return items;
}

void XlsxParser::createPage(QString file, QString page) {
    xlnt::workbook wb;
    wb.load(file.toStdString());
    auto sheet = wb.create_sheet();
    sheet.title(page.toStdString());
    wb.save(file.toStdString());
}

void XlsxParser::removePage(QString file, QString page) {
	std::cout << "Excel" << std::endl;
}

void XlsxParser::setData(QString file, QString page, QVector<SheetItem> items) {
    xlnt::workbook wb;
    wb.load(file.toStdString());
    auto sheet = wb.sheet_by_title(page.toStdString());

    for (SheetItem item : items) {
        QTableWidget *current = TabWidget::currentWidget()->currentTable();
        QString cellStr = current->horizontalHeaderItem(item.y)->text();
        cellStr+=QString::number(item.x+1);
        auto cell = sheet.cell(cellStr.toStdString());
        cell.value(item.data.toStdString());
    }

    wb.save(file.toStdString());
}

void XlsxParser::setMathData(QString file, QString page, QVector<MathItem> items) {
    xlnt::workbook wb;
    wb.load(file.toStdString());
    auto sheet = wb.sheet_by_title(page.toStdString());

    for (MathItem item : items) {
        QTableWidget *current = TabWidget::currentWidget()->currentTable();
        QString cellStr = current->horizontalHeaderItem(item.y)->text();
        cellStr+=QString::number(item.x+1);
        auto cell = sheet.cell(cellStr.toStdString());
        cell.formula(item.equation.toStdString());
    }

    wb.save(file.toStdString());
}

