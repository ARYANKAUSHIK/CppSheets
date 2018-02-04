#include <QVariant>
#include <iostream>

#include "parser.hh"

QStringList Parser::pages(QString file) {
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

bool Parser::pageExists(QString file, QString pageName) {
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

QVector<SheetItem> Parser::allItems(QString file, QString page) {
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

QVector<MathItem> Parser::allMathItems(QString file, QString page) {
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

void Parser::createPage(QString file, QString page) {
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

    doc->SaveFile(file.toStdString().c_str());
}

void Parser::removePage(QString file, QString page) {
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

void Parser::setData(QString file, QString page, QVector<SheetItem> items) {
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
    }

    doc->SaveFile(file.toStdString().c_str());
}

void Parser::setMathData(QString file, QString page, QVector<MathItem> items) {
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

XMLElement *Parser::getPageElement(XMLElement *root, QString title) {
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
