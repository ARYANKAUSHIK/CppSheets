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
#include <QFile>
#include <QTextStream>
#include <QVariant>
#include <iostream>

#include "xml_parser.hh"

void XmlParser::createFile(QString filePath) {
    QFile file(filePath);
    if (file.open(QFile::ReadWrite | QFile::Truncate)) {
        QTextStream writer(&file);
        QString content = "<?xml version=\"1.0\"?>\n"
                          "<sheet>\n</sheet>\n";
        writer << content;
        writer.flush();
        file.close();
    }
}

QStringList XmlParser::pages(QString file) {
	QStringList list;
	
	XMLDocument *doc = new XMLDocument;
	doc->LoadFile(file.toStdString().c_str());

    XMLElement *root = doc->FirstChildElement("sheet");
    if (root==nullptr) {
        return list;
    }

    XMLElement *page = root->FirstChildElement("page");
    XMLElement *lastPage;

    while (page!=nullptr) {
        QString name = QString(page->Attribute("title"));
        if (!name.isNull()) {
            list.push_back(name);
        }

        lastPage = page;
        page = lastPage->NextSiblingElement("page");
    }
	
	return list;
}

bool XmlParser::pageExists(QString file, QString pageName) {
    bool ret = false;

    XMLDocument *doc = new XMLDocument;
    doc->LoadFile(file.toStdString().c_str());

    XMLElement *root = doc->FirstChildElement("sheet");
    if (root==nullptr) {
        return ret;
    }

    XMLElement *page = root->FirstChildElement("page");
    XMLElement *lastPage;

    while (page!=nullptr) {
        QString name = QString(page->Attribute("title"));
        if (!name.isNull()) {
            if (name==pageName) {
                ret = true;
                break;
            }
        }

        lastPage = page;
        page = lastPage->NextSiblingElement("page");
    }

    return ret;
}

QVector<SheetItem> XmlParser::allItems(QString file, QString page) {
    QVector<SheetItem> items;

    XMLDocument *doc = new XMLDocument;
    doc->LoadFile(file.toStdString().c_str());

    XMLElement *root = doc->FirstChildElement("sheet");
    if (root==nullptr) {
        return items;
    }

    XMLElement *pageElement = getPageElement(root,page);
    if (pageElement==nullptr) {
        return items;
    }

    XMLElement *dataElement = pageElement->FirstChildElement("data");
    if (dataElement==nullptr) {
        return items;
    }

    XMLElement *td = dataElement->FirstChildElement("td");
    XMLElement *tdOld;

    while (td!=nullptr) {
        SheetItem item;
        QString sx = QString(td->Attribute("x"));
        QString sy = QString(td->Attribute("y"));
        QString text = QString(td->GetText());

        QString bgColor = QString(td->Attribute("bgColor"));
        if (bgColor.isNull()) {
            item.bgColor = Qt::white;
        } else {
            item.bgColor = QColor(bgColor);
        }

        QString fgColor = QString(td->Attribute("fgColor"));
        if (fgColor.isNull()) {
            item.fgColor = Qt::black;
        } else {
            item.fgColor = QColor(fgColor);
        }

        QString tooltip = QString(td->Attribute("tooltip"));
        if (!tooltip.isNull()) {
            item.tooltip = tooltip;
        }

        QString colWidthStr = QString(td->Attribute("colwidth"));
        int colWidth = QVariant(colWidthStr).toInt();
        item.colWidth = colWidth;

        QString rowWidthStr = QString(td->Attribute("rowwidth"));
        int rowWidth = QVariant(rowWidthStr).toInt();
        item.rowWidth = rowWidth;

        QString sSpanX = QString(td->Attribute("spanx"));
        int spanX = QVariant(sSpanX).toInt();
        item.spanx = spanX;

        QString sSpanY = QString(td->Attribute("spany"));
        int spanY = QVariant(sSpanY).toInt();
        item.spany = spanY;

        QString sBold = QString(td->Attribute("bold"));
        QString sItalic = QString(td->Attribute("italic"));
        QString sUnderline = QString(td->Attribute("underline"));
        QString fontFamily = QString(td->Attribute("font-family"));
        QString sFontSize = QString(td->Attribute("font-size"));

        QFont font;
        font.setBold(QVariant(sBold).toBool());
        font.setItalic(QVariant(sItalic).toBool());
        font.setUnderline(QVariant(sUnderline).toBool());
        font.setFamily(fontFamily);
        font.setPointSize(QVariant(sFontSize).toInt());
        item.font = font;

        item.border = QString(td->Attribute("border"));

        if ((!sx.isNull())||(!sy.isNull())||(!text.isNull())) {
            item.x = QVariant(sx).toInt();
            item.y = QVariant(sy).toInt();
            item.data = text;
            items.push_back(item);
        }

        tdOld = td;
        td = tdOld->NextSiblingElement("td");
    }

    return items;
}

QVector<MathItem> XmlParser::allMathItems(QString file, QString page) {
    QVector<MathItem> items;

    XMLDocument *doc = new XMLDocument;
    doc->LoadFile(file.toStdString().c_str());

    XMLElement *root = doc->FirstChildElement("sheet");
    if (root==nullptr) {
        return items;
    }

    XMLElement *pageElement = getPageElement(root,page);
    if (pageElement==nullptr) {
        return items;
    }

    XMLElement *mathElement = pageElement->FirstChildElement("math");
    if (mathElement==nullptr) {
        return items;
    }

    XMLElement *td = mathElement->FirstChildElement("equ");
    XMLElement *tdOld;

    while (td!=nullptr) {
        MathItem item;
        QString sx = QString(td->Attribute("x"));
        QString sy = QString(td->Attribute("y"));
        QString equation = QString(td->GetText());

        if ((!sx.isNull())||(!sy.isNull())||(!equation.isNull())) {
            item.x = QVariant(sx).toInt();
            item.y = QVariant(sy).toInt();
            item.equation = equation;
            items.push_back(item);
        }

        tdOld = td;
        td = tdOld->NextSiblingElement("equ");
    }

    return items;
}

void XmlParser::createPage(QString file, QString page) {
    XMLDocument *doc = new XMLDocument;
    doc->LoadFile(file.toStdString().c_str());

    XMLElement *root = doc->FirstChildElement("sheet");
    if (root==nullptr) {
        return;
    }

    XMLElement *newPage = doc->NewElement("page");
    newPage->SetAttribute("title",page.toStdString().c_str());
    root->InsertEndChild(newPage);

    XMLElement *newData = doc->NewElement("data");
    newPage->InsertFirstChild(newData);

    XMLElement *newMath = doc->NewElement("math");
    newPage->InsertFirstChild(newMath);

    doc->SaveFile(file.toStdString().c_str());
}

void XmlParser::removePage(QString file, QString page) {
    XMLDocument *doc = new XMLDocument;
    doc->LoadFile(file.toStdString().c_str());

    XMLElement *root = doc->FirstChildElement("sheet");
    if (root==nullptr) {
        return;
    }

    XMLElement *toDelete = getPageElement(root,page);
    root->DeleteChild(toDelete);

    doc->SaveFile(file.toStdString().c_str());
}

void XmlParser::setData(QString file, QString page, QVector<SheetItem> items) {
    XMLDocument *doc = new XMLDocument;
    doc->LoadFile(file.toStdString().c_str());

    XMLElement *root = doc->FirstChildElement("sheet");
    if (root==nullptr) {
        return;
    }

    XMLElement *pageElement = getPageElement(root,page);
    if (pageElement==nullptr) {
        return;
    }

    XMLElement *dataElement = pageElement->FirstChildElement("data");
    if (dataElement==nullptr) {
        return;
    }
    dataElement->DeleteChildren();

    for (int i = 0; i<items.size(); i++) {
        SheetItem current = items.at(i);
        QString sx = QVariant(current.x).toString();
        QString sy = QVariant(current.y).toString();

        XMLElement *td = doc->NewElement("td");
        dataElement->InsertEndChild(td);

        td->SetAttribute("x",sx.toStdString().c_str());
        td->SetAttribute("y",sy.toStdString().c_str());
        td->SetText(current.data.toStdString().c_str());

        QString fgColor = current.fgColor.name();
        if (!fgColor.isNull()) {
            td->SetAttribute("fgColor",fgColor.toStdString().c_str());
        }

        QString bgColor = current.bgColor.name();
        if (!bgColor.isNull()) {
            td->SetAttribute("bgColor",bgColor.toStdString().c_str());
        }

        QString tooltip = current.tooltip;
        if (!tooltip.isNull()) {
            td->SetAttribute("tooltip",tooltip.toStdString().c_str());
        }

        int colWidth = current.colWidth;
        QString colWidthStr = QVariant(colWidth).toString();
        td->SetAttribute("colwidth",colWidthStr.toStdString().c_str());

        int rowWidth = current.rowWidth;
        QString rowWidthStr = QVariant(rowWidth).toString();
        td->SetAttribute("rowwidth",rowWidthStr.toStdString().c_str());

        QString spanX = QVariant(current.spanx).toString();
        td->SetAttribute("spanx",spanX.toStdString().c_str());

        QString spanY = QVariant(current.spany).toString();
        td->SetAttribute("spany",spanY.toStdString().c_str());

        if (current.font.bold()) {
            td->SetAttribute("bold","true");
        } else {
            td->SetAttribute("bold","false");
        }

        if (current.font.italic()) {
            td->SetAttribute("italic","true");
        } else {
            td->SetAttribute("italic","false");
        }

        if (current.font.underline()) {
            td->SetAttribute("underline","true");
        } else {
            td->SetAttribute("underline","false");
        }

        td->SetAttribute("font-family",current.font.family().toStdString().c_str());
        td->SetAttribute("font-size",QVariant(current.font.pointSize())
                         .toString().toStdString().c_str());

        td->SetAttribute("border",current.border.toStdString().c_str());
    }

    doc->SaveFile(file.toStdString().c_str());
}

void XmlParser::setMathData(QString file, QString page, QVector<MathItem> items) {
    XMLDocument *doc = new XMLDocument;
    doc->LoadFile(file.toStdString().c_str());

    XMLElement *root = doc->FirstChildElement("sheet");
    if (root==nullptr) {
        return;
    }

    XMLElement *pageElement = getPageElement(root,page);
    if (pageElement==nullptr) {
        return;
    }

    XMLElement *mathElement = pageElement->FirstChildElement("math");
    if (mathElement==nullptr) {
        return;
    }
    mathElement->DeleteChildren();

    for (int i = 0; i<items.size(); i++) {
        MathItem current = items.at(i);
        QString sx = QVariant(current.x).toString();
        QString sy = QVariant(current.y).toString();

        XMLElement *td = doc->NewElement("equ");
        mathElement->InsertEndChild(td);

        td->SetAttribute("x",sx.toStdString().c_str());
        td->SetAttribute("y",sy.toStdString().c_str());
        td->SetText(current.equation.toStdString().c_str());
    }

    doc->SaveFile(file.toStdString().c_str());
}

XMLElement *XmlParser::getPageElement(XMLElement *root, QString title) {
    XMLElement *pageElement = root->FirstChildElement("page");
    XMLElement *oldPage;
    while (pageElement!=nullptr) {
        QString pgTitle = pageElement->Attribute("title");
        if (pgTitle==title) {
            break;
        }
        oldPage = pageElement;
        pageElement = oldPage->NextSiblingElement("page");
    }
    return pageElement;
}
