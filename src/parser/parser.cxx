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
#include <iostream>
#include <QFile>

#include "parser.hh"
#include "xml_parser.hh"
#include "xlsx_parser.hh"
#include "csv_parser.hh"

void Parser::createFile(QString filePath) {
	if (isXlsx(filePath)) {
		XlsxParser::createFile(filePath);
	} else {
		XmlParser::createFile(filePath);
	}
}

QStringList Parser::pages(QString file) {
	if (isXlsx(file)) {
		return XlsxParser::pages(file);
    } else if (file.endsWith(".csv")) {
        //TODO: Clean this up
        QFile f(file);
        QString name = f.fileName();
        QStringList pages;
        pages << name;
        return pages;
	} else {
		return XmlParser::pages(file);
	}
}

bool Parser::pageExists(QString file, QString pageName) {
	if (isXlsx(file)) {
		return XlsxParser::pageExists(file,pageName);
	} else {
		return XmlParser::pageExists(file,pageName);
	}
}

QVector<SheetItem> Parser::allItems(QString file, QString page) {
	if (isXlsx(file)) {
		return XlsxParser::allItems(file,page);
    } else if (file.endsWith(".csv")) {
        return CsvParser::allItems(file,page);
	} else {
		return XmlParser::allItems(file,page);
	}
}

QVector<MathItem> Parser::allMathItems(QString file, QString page) {
	if (isXlsx(file)) {
		return XlsxParser::allMathItems(file,page);
	} else {
		return XmlParser::allMathItems(file,page);
	}
}

void Parser::createPage(QString file, QString page) {
	if (isXlsx(file)) {
		XlsxParser::createPage(file,page);
	} else {
		XmlParser::createPage(file,page);
	}	
}

void Parser::removePage(QString file, QString page) {
	if (isXlsx(file)) {
		XlsxParser::removePage(file,page);
	} else {
		XmlParser::removePage(file,page);
	}
}

void Parser::setData(QString file, QString page, QVector<SheetItem> items) {
	if (isXlsx(file)) {
		XlsxParser::setData(file,page,items);
	} else {
		XmlParser::setData(file,page,items);
	}
}

void Parser::setMathData(QString file, QString page, QVector<MathItem> items) {
	if (isXlsx(file)) {
		XlsxParser::setMathData(file,page,items);
	} else {
		XmlParser::setMathData(file,page,items);
	}
}

bool Parser::isXlsx(QString file) {
	if (file.endsWith(".xlsx")) {
		return true;
	} else {
		return false;
	}
}

