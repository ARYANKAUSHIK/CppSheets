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

#include "math.hh"
#include "formula_utils.hh"
#include "../sheetwidget.hh"
#include "../tabwidget.hh"

void Math::updateMath(QVector<MathItem> mathItems, TableWidget *table) {
    for (int i = 0; i<mathItems.size(); i++) {
        MathItem current = mathItems.at(i);
        QString name = formulaName(current.equation);
        QString equ = formulaEqu(current.equation);

        if (name=="SUM") {
            QStringList range = rangeContents(equ,table);

            double answer = 0;

            for (int i = 0; i<range.size(); i++) {
                double c = QVariant(range.at(i)).toDouble();
                answer+=c;
            }

            printResult(answer,current,table);
        } else {
            if (equ.length()==0) {
                QStringList objects;

                QString currentS = "";
                for (int i = 1; i<current.equation.length(); i++) {
                    QChar c = current.equation.at(i);
                    if (c=='+' || c=='-' || c=='*' || c=='/') {
                        QChar c1 = currentS.at(0);
                        if (c1.isLetter()) {
                            Cell cell = cellFromName(currentS,table);
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
                    Cell cell = cellFromName(currentS,table);
                    currentS = cell.content;
                }
                objects.push_back(currentS);

                double answer = solve(objects);
                printResult(answer,current,table);
            } else {
                //Unknown formula name
                //std::cout << "Unknown formula" << std::endl;
                /*QMessageBox msg;
                msg.setText("Error: Unknown formula.");
                msg.setDetailedText(current.equation);
                msg.setWindowTitle("Error");
                msg.setIcon(QMessageBox::Critical);
                msg.exec();*/
            }
        }
    }
}

//This returns the formula's name.
QString Math::formulaName(QString equation) {
    QString name = "";

    for (int i = 1; i<equation.length(); i++) {
        if (equation.at(i)=='(') {
            break;
        }
        name+=equation.at(i);
    }

    return name;
}

//This returns the formula's content
QString Math::formulaEqu(QString equation) {
    QString ret = "";
    bool in = false;

    for (int i = 1; i<equation.length(); i++) {
        if (equation.at(i)=='(') {
            in = true;
        } else if (equation.at(i)==')') {
            break;
        } else {
            if (in) {
                ret+=equation.at(i);
            }
        }
    }

    return ret;
}

//All the items within a particular rnage
QStringList Math::rangeContents(QString range, TableWidget *table) {
    QStringList ret;

    //First, break up the range
    QString start = "";
    QString end = "";
    bool found = false;

    for (int i = 0; i<range.length(); i++) {
        if (range.at(i)==':') {
            found = true;
        } else {
            if (found) {
                end+=range.at(i);
            } else {
                start+=range.at(i);
            }
        }
    }

    //Get cell locations and contents
    Cell startC = cellFromName(start,table);
    Cell endC = cellFromName(end,table);

    //Now, we must see which direction we are going (horizontal or vertical)
    ret.push_back(startC.content);

    if (startC.x!=endC.x) {
        //We are going across
        for (int i = startC.x+1; i<=endC.x; i++) {
            QTableWidgetItem *item = table->item(startC.y,i);
            if (item!=nullptr) {
                ret.push_back(item->text());
            }
        }
    } else {
        //We are going vertically
        for (int i = startC.y+1; i<endC.y; i++) {
            QTableWidgetItem *item = table->item(i,startC.x);
            if (item!=nullptr) {
                ret.push_back(item->text());
            }
        }
    }

    ret.push_back(endC.content);

    //Go through the list and remove and blank entries
    QStringList list2;

    for (int i = 0; i<ret.size(); i++) {
        QString current = ret.at(i);
        if (current.length()>0) {
            list2.push_back(current);
        }
    }

    ret = list2;

    return ret;
}

Cell Math::cellFromName(QString name, TableWidget *table) {
    Cell c;

    //Separate the string into parts
    QString part1 = "";
    QString part2 = "";

    for (int i = 0; i<name.length(); i++) {
        if (name.at(i).isNumber()) {
            part2+=name.at(i);
        } else {
            part1+=name.at(i);
        }
    }

    //Part 1 corresponds to the X var, so get the header that
    //matches the part1 var
    int h_count = table->horizontalHeader()->count();
    for (int i = 0; i<h_count; i++) {
        if (table->horizontalHeaderItem(i)->text()==part1) {
            c.x = i;
            break;
        }
    }

    //Part 2 corresponds to the Y var, so go ahead and convert
    c.y = QVariant(part2).toInt();
    c.y = c.y-1;

    //We now have a valid location. Get the content.
    QTableWidgetItem *item = table->item(c.y,c.x);
    if (item==nullptr) {
        c.content = "";
    } else {
        c.content = item->text();
    }

    return c;
}

//Solves a column of objects
double Math::solve(QStringList objects) {
    double result = QVariant(objects.at(0)).toDouble();

    int len = objects.length();
    for (int i = 1; i<len; i+=2) {
        double no = QVariant(objects.at(i+1)).toDouble();
        QString op = objects.at(i);
        if (op=="+") {
            result+=no;
        } else if (op=="-") {
            result-=no;
        } else if (op=="*") {
            result*=no;
        } else if (op=="/") {
            result/=no;
        }
    }

    return result;
}

//This prints the results of our calculations to the table
void Math::printResult(double answer, MathItem current, TableWidget *table) {
    QString answerStr = QVariant(answer).toString();

    QTableWidgetItem *item = table->item(current.x,current.y);
    if (item==nullptr) {
        item = new QTableWidgetItem;
    }
    item->setText(answerStr);
    table->setItem(current.x,current.y,item);
}
