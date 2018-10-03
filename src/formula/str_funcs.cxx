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
#include "str_funcs.hh"
#include "formula_utils.hh"

//The code for the LEN formula
QString StrFuncs::len(QString equ, TableWidget *table) {
    QString ln = getInner(equ,table);

    if (ln!="ERR") {
        ln = QVariant(ln.length()).toString();
    }

    return ln;
}

//The code for the UPPER formula
QString StrFuncs::upper(QString equ, TableWidget *table) {
    QString ln = getInner(equ,table);

    if (ln!="ERR") {
        ln = ln.toUpper();
    }

    return ln;
}

//The code for the LOWER formula
QString StrFuncs::lower(QString equ, TableWidget *table) {
    QString ln = getInner(equ,table);

    if (ln!="ERR") {
        ln = ln.toLower();
    }

    return ln;
}

//Returns the inside of String functions
QString StrFuncs::getInner(QString equ, TableWidget *table) {
    QString ln = "";

    if (equ.at(0)=='\"' && equ.at(equ.length()-1)=='\"') {
        ln = equ;
        ln.remove(0,1);
        ln.remove(ln.length()-1,ln.length()-1);
    } else if (equ.at(0).isLetter()) {
        ln = FormulaUtils::cellFromName(equ,table).content;
    } else {
        ln = "ERR";
    }

    return ln;
}
