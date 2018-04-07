// Copyright 2018 Patrick Flynn
//
// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, 
//	this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this 
//	list of conditions and the following disclaimer in the documentation and/or 
//	other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may 
//	be used to endorse or promote products derived from this software 
//	without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
    for (auto row : sheet.rows()) {
        c = 0;
        for (auto cell : row) {
            SheetItem item;
            item.data = QString::fromStdString(cell.to_string());
            item.x = r;
            item.y = c;
            item.bgColor = Qt::white;
            item.fgColor = Qt::black;
            item.spanx = 1;
            item.spany = 1;
            item.colWidth = cell.width();
            item.rowWidth = cell.height();
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

