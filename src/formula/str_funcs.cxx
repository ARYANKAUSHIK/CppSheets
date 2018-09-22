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
