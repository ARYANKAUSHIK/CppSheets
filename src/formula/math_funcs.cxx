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
#include <cmath>

#include "math_funcs.hh"
#include "formula_utils.hh"

//The logic for the ABS formula
double MathFuncs::abs(QString equ, TableWidget *table) {
    //First, see if we are referencing a number or a cell
    if (equ.at(0).isLetter()) {
        equ = FormulaUtils::cellFromName(equ,table).content;
    }

    //Convert to a number
    double no = QVariant(equ).toDouble();

    //Calculate and return
    double result = std::abs(no);
    return result;
}

//The logic for the POWER formula
double MathFuncs::pow(QString equ, TableWidget *table) {
    //First, separate the string
    QString part1 = "", part2 = "";
    bool found = false;

    for (QChar c : equ) {
        if (c==',') {
            found = true;
        } else {
            if (found) {
                part1+=c;
            } else {
                part2+=c;
            }
        }
    }

    //If either of the strings start with a letter, we have a cell
    //Otherwise, we have a number
    if (part1.at(0).isLetter()) {
        part1 = FormulaUtils::cellFromName(part1,table).content;
    }

    if (part2.at(0).isLetter()) {
        part2 = FormulaUtils::cellFromName(part2,table).content;
    }

    //Now, convert both to numbers
    //In case we have decimals, we want doubles
    double no1 = QVariant(part1).toDouble();
    double no2 = QVariant(part2).toDouble();

    //Calculate
    double result = std::pow(no2,no1);
    return result;
}
