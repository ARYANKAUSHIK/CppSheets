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
#include <QFile>
#include <QTextStream>
#include <iostream>

#include "csv_parser.hh"

SheetItem defaultItem() {
    SheetItem item;
    item.bgColor = Qt::white;
    item.fgColor = Qt::black;
    item.spanx = 0;
    item.spany = 0;
    item.colWidth = 10;
    item.rowWidth = 10;
    return item;
}

QVector<SheetItem> CsvParser::allItems(QString file, QString page) {
    QVector<SheetItem> items;
    
    auto lines = fileLines(file);
    int x = 0;
    int y = 0;
    
    for (QString ln : lines) {
        y = 0;
        auto parts = lineParts(ln);
        
        for (QString ln2 : parts) {
            SheetItem item = defaultItem();
            item.data = ln2;
            item.x = x;
            item.y = y;
            items.push_back(item);
            
            y++;
        }
        
        x++;
    }
    
    return items;
}

QStringList CsvParser::fileLines(QString file) {
    QStringList lines;
    
    QFile f(file);
    if (f.open(QFile::ReadWrite)) {
        QTextStream reader(&f);
        
        while (!reader.atEnd()) {
            QString line = reader.readLine();
            lines.append(line);
        }
    }
    
    return lines;
}

QStringList CsvParser::lineParts(QString line) {
    QStringList parts;
    
    QString current = "";
    bool inQuotes = false;
    
    for (QChar c : line) {
        if ((c==',' || c==';') && inQuotes==false) {
            parts << current;
            current = "";
        } else if (c=='\"') {
            if (inQuotes) {
                inQuotes = false;
            } else {
                inQuotes = true;
            }
        } else {
            current += c;
        }
    }
    
    parts << current;
    
    return parts;
}
