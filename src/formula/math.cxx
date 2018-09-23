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
#include "math_funcs.hh"
#include "str_funcs.hh"
#include "../sheetwidget.hh"
#include "../tabwidget.hh"

void Math::updateMath(QVector<MathItem> mathItems, TableWidget *table) {

    for (int i = 0; i<mathItems.size(); i++) {
        MathItem current = mathItems.at(i);
        QString name = FormulaUtils::formulaName(current.equation);
        QString equ = FormulaUtils::formulaEqu(current.equation);

        interpret(name,equ,current,table);
    }
}

//The main interpreter function
bool Math::interpret(QString name, QString equ, MathItem current, TableWidget *table) {
    bool ret = true;

    //The SUM function
    if (name=="SUM") {
        double answer = MathFuncs::sum(equ,table);
        FormulaUtils::printResult(answer,current,table);

    //The AVERAGE function
    } else if (name=="AVERAGE") {
        double answer = MathFuncs::average(equ,table);
        FormulaUtils::printResult(answer,current,table);

    //The ABS function
    } else if (name=="ABS") {
        double answer = MathFuncs::abs(equ,table);
        FormulaUtils::printResult(answer,current,table);

    //The POWER function
    } else if (name=="POWER") {
        double result = MathFuncs::pow(equ,table);
        FormulaUtils::printResult(result,current,table);

    //The LEN function (string length)
    } else if (name=="LEN") {
        QString result = StrFuncs::len(equ,table);
        FormulaUtils::printResult(result,current,table);

    //Converts the contents of a cell to lowercase
    } else if (name=="LOWER") {
        QString answer = StrFuncs::lower(equ,table);
        FormulaUtils::printResult(answer,current,table);

    //Converts the contents of a cell to uppercase
    } else if (name=="UPPER") {
        QString answer = StrFuncs::upper(equ,table);
        FormulaUtils::printResult(answer,current,table);

    //The ACOS formula
    } else if (name=="ACOS") {
        double result = MathFuncs::acos(equ,table);
        FormulaUtils::printResult(result,current,table);

    //The ACOSH formula
    } else if (name=="ACOSH") {
        double result = MathFuncs::acosh(equ,table);
        FormulaUtils::printResult(result,current,table);

    //The COS formula
    } else if (name=="COS") {
        double result = MathFuncs::cos(equ,table);
        FormulaUtils::printResult(result,current,table);

    //The SIN formula
    } else if (name=="SIN") {
        double result = MathFuncs::sin(equ,table);
        FormulaUtils::printResult(result,current,table);

    //The TAN formula
    } else if (name=="TAN") {
        double result = MathFuncs::tan(equ,table);
        FormulaUtils::printResult(result,current,table);

    //Other functions and utilities
    //Note: Most formulas past this point are handeled by separate functions
    } else if (name=="IF") {
        solveIF(equ,current,table);
    } else {
        //Used for column functions
        if (equ.length()==0) {
            solveColumn(current,table);
        } else {
            //Unknown formula name
            std::cout << "Unknown formula" << std::endl;
            ret = false;
        }
    }

    return ret;
}

//Solves and IF function
void Math::solveIF(QString statement, MathItem current, TableWidget *table) {
    //First, break up the string
    QString toCheck = "";
    QString trueStr = "";
    QString falseStr = "";

    bool fc1 = false;
    bool fc2 = false;
    for (int i = 0; i<statement.length(); i++) {
        if (statement.at(i)==',') {
            if (!fc1) {
                fc1 = true;
            } else {
                fc2 = true;
            }
        } else {
            if (fc1 && fc2) {
                falseStr+=statement.at(i);
            } else if (fc1) {
                trueStr+=statement.at(i);
            } else {
                toCheck+=statement.at(i);
            }
        }
    }

    //Now, parse the conditional statement
    QString cell = "";
    QString data = "";

    bool fe = false;
    QChar middle = ' ';
    for (int i = 0; i<toCheck.length(); i++) {
        if (toCheck.at(i)=='=' || toCheck.at(i)=='>' || toCheck.at(i)=='<') {
            middle = toCheck.at(i);
            fe = true;
        } else {
            if (fe) {
                data+=toCheck.at(i);
            } else {
                cell+=toCheck.at(i);
            }
        }
    }

    //Remove quotation marks
    if (data.at(0)=='\"' || data.at(data.length()-1)=='\"') {
        data.remove(0,1);
        data.remove(data.length()-1,data.length()-1);
    }

    if (trueStr.at(0)=='\"' || trueStr.at(trueStr.length()-1)=='\"') {
        trueStr.remove(0,1);
        trueStr.remove(trueStr.length()-1,trueStr.length()-1);
    }

    if (falseStr.at(0)=='\"' || falseStr.at(falseStr.length()-1)=='\"') {
        falseStr.remove(0,1);
        falseStr.remove(falseStr.length()-1,falseStr.length()-1);
    }

    //Get the target cell content and compare
    Cell c = FormulaUtils::cellFromName(cell,table);
    QString cell_data = c.content;
    QString result = "";

    if (middle=='=') {
        if (data==cell_data) {
            result = trueStr;
        } else {
            result = falseStr;
        }

    } else {
        double no1 = QVariant(cell_data).toDouble();
        double no2 = QVariant(data).toDouble();

        result = falseStr;

        if (middle=='>') {
            if (no1>no2) {
                result = trueStr;
            }
        } else {
            if (no1<no2) {
                result = trueStr;
            }
        }
    }

    //Set the data
    QString fName = FormulaUtils::formulaName(result);
    QString fEqu = FormulaUtils::formulaEqu(result);

    if (fName.length()>0 && fEqu.length()==0) {
        FormulaUtils::printResult(result,current,table);
    } else {
        if (!interpret(fName,fEqu,current,table)) {
            FormulaUtils::printResult(result,current,table);
        }
    }
}

//Solves a column
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
