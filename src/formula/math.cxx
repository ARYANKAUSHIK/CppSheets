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
#include <QHeaderView>
#include <QMessageBox>
#include <iostream>
#include <cmath>

#include "math.hh"
#include "formula_utils.hh"
#include "../sheetwidget.hh"
#include "../tabwidget.hh"

void Math::updateMath(QVector<MathItem> mathItems, TableWidget *table) {
    for (int i = 0; i<mathItems.size(); i++) {
        MathItem current = mathItems.at(i);
        QString name = FormulaUtils::formulaName(current.equation);
        QString equ = FormulaUtils::formulaEqu(current.equation);

        //The SUM function
        if (name=="SUM") {
            QStringList range = FormulaUtils::rangeContents(equ,table);

            double answer = 0;

            for (int i = 0; i<range.size(); i++) {
                double c = QVariant(range.at(i)).toDouble();
                answer+=c;
            }

            FormulaUtils::printResult(answer,current,table);
        } else if (name=="ABS") {
            Cell c = FormulaUtils::cellFromName(equ,table);
            double result = QVariant(c.content).toDouble();
            double answer = std::abs(result);
            FormulaUtils::printResult(answer,current,table);
        } else {
            //Used for column functions
            if (equ.length()==0) {
                solveColumn(current,table);
            } else {
                //Unknown formula name
                std::cout << "Unknown formula" << std::endl;
            }
        }
    }
}

void Math::solveColumn(MathItem current, TableWidget *table) {
    QStringList objects;

    QString currentS = "";
    for (int i = 1; i<current.equation.length(); i++) {
        QChar c = current.equation.at(i);
        if (c=='+' || c=='-' || c=='*' || c=='/') {
            QChar c1 = currentS.at(0);
            if (c1.isLetter()) {
                Cell cell = FormulaUtils::cellFromName(currentS,table);
                currentS = cell.content;
            }
            objects.push_back(currentS);
            currentS = "";

            QString sym = "";
            sym+=c;
            objects.push_back(c);
        } else {
            currentS+=c;
        }
    }

    QChar c1 = currentS.at(0);
    if (c1.isLetter()) {
        Cell cell = FormulaUtils::cellFromName(currentS,table);
        currentS = cell.content;
    }
    objects.push_back(currentS);

    double answer = FormulaUtils::solve(objects);
    FormulaUtils::printResult(answer,current,table);
}
