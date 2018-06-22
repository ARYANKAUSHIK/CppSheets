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
#include <QColorDialog>

#include "format_actions.hh"
#include "../tabwidget.hh"
#include "../parser/parser.hh"
#include "../sheetwidget.hh"

void FormatActions::bold() {
    SheetWidget *sheet = TabWidget::currentWidget();
    QTableWidgetItem *item = sheet->currentCell();
    QFont font = item->font();
    if (font.bold()) {
        font.setBold(false);
    } else {
        font.setBold(true);
    }
    item->setFont(font);
}

void FormatActions::italic() {
    SheetWidget *sheet = TabWidget::currentWidget();
    QTableWidgetItem *item = sheet->currentCell();
    QFont font = item->font();
    if (font.italic()) {
        font.setItalic(false);
    } else {
        font.setItalic(true);
    }
    item->setFont(font);
}

void FormatActions::underline() {
    SheetWidget *sheet = TabWidget::currentWidget();
    QTableWidgetItem *item = sheet->currentCell();
    QFont font = item->font();
    if (font.underline()) {
        font.setUnderline(false);
    } else {
        font.setUnderline(true);
    }
    item->setFont(font);
}

void FormatActions::bgColor() {
    QColor color = QColorDialog::getColor();
    SheetWidget *current = TabWidget::currentWidget();
    if (current->currentTable()->currentSelectedItems().size()==1) {
        TabWidget::currentWidget()->currentCell()->setBackgroundColor(color);
    } else {
        auto list = current->currentTable()->currentSelectedItems();
        for (auto item : list) {
            int col = item.column();
            int row = item.row();

            QTableWidgetItem *tItem = current->currentTable()->item(row,col);
            if (tItem==nullptr) {
                tItem = new QTableWidgetItem();
                current->currentTable()->setItem(row,col,tItem);
            }
            tItem->setBackgroundColor(color);
        }
    }
}

void FormatActions::fgColor() {
    QColor color = QColorDialog::getColor(Qt::black);
    SheetWidget *current = TabWidget::currentWidget();
    if (current->currentTable()->currentSelectedItems().size()==1) {
        TabWidget::currentWidget()->currentCell()->setTextColor(color);
    } else {
        auto list = current->currentTable()->currentSelectedItems();
        for (auto item : list) {
            int col = item.column();
            int row = item.row();

            QTableWidgetItem *tItem = current->currentTable()->item(row,col);
            if (tItem==nullptr) {
                tItem = new QTableWidgetItem();
                current->currentTable()->setItem(row,col,tItem);
            }
            tItem->setTextColor(color);
        }
    }
}

void FormatActions::merge() {
    TabWidget::currentWidget()->mergeSelected();
}

void FormatActions::unMerge() {
    TabWidget::currentWidget()->unMergeSelected();
}

void FormatActions::dspBorderDialog() {
    BorderDialog dialog;
    dialog.exec();
}

//=========================================================
//The border dialog
BorderDialog::BorderDialog()
    : colorWidget(new QFrame),
      widthWidget(new QFrame),
      typeWidget(new QFrame),
      mainLayout(new QVBoxLayout),
      colorLayout(new QHBoxLayout),
      widthLayout(new QHBoxLayout),
      typeLayout(new QHBoxLayout),
      borderTypes(new QComboBox)
{
    this->setWindowTitle("Set Cell Border");
    this->setFixedSize(300,200);

    mainLayout->setContentsMargins(0,0,0,0);
    this->setLayout(mainLayout);

    //===The border color controls===
    colorWidget->setLayout(colorLayout);

    chooseColor = new QPushButton("Choose Color");
    connect(chooseColor,&QPushButton::clicked,this,&BorderDialog::onColorChanged);

    colorLayout->addWidget(new QLabel("Choose color: "));
    colorLayout->addWidget(chooseColor);

    mainLayout->addWidget(colorWidget);

    //===The border width controls===
    widthWidget->setLayout(widthLayout);

    widthSpinner = new QSpinBox;
    widthSpinner->setMinimum(1);
    widthSpinner->setMaximum(100);
    widthSpinner->setValue(3);
    connect(widthSpinner,SIGNAL(valueChanged(int)),this,SLOT(onWidthChanged()));

    widthLayout->addWidget(new QLabel("Set width: "));
    widthLayout->addWidget(widthSpinner);

    mainLayout->addWidget(widthWidget);

    //===The border type controls===
    typeWidget->setLayout(typeLayout);

    borderTypes->addItem("solid");
    borderTypes->addItem("dash");
    borderTypes->addItem("dot");
    borderTypes->addItem("dash_dot");
    borderTypes->addItem("dash_dot_dot");
    connect(borderTypes,&QComboBox::currentTextChanged,this,&BorderDialog::onTypeChanged);

    typeLayout->addWidget(new QLabel("Choose border type: "));
    typeLayout->addWidget(borderTypes);

    mainLayout->addWidget(typeWidget);

    //The dialog buttons
    dialogButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(dialogButtons,&QDialogButtonBox::accepted,this,&BorderDialog::onClose);
    connect(dialogButtons,&QDialogButtonBox::rejected,this,&BorderDialog::close);

    mainLayout->addWidget(dialogButtons);
}

BorderDialog::~BorderDialog() {
    /*delete mainWidget;
    delete colorWidget;
    delete widthWidget;
    delete typeWidget;
    delete mainLayout;
    delete colorLayout;
    delete widthLayout;
    delete typeLayout;*/
}

void BorderDialog::onColorChanged() {
    QColor c = QColorDialog::getColor();
    color = c.name();
}

void BorderDialog::onWidthChanged() {
    width = QVariant(widthSpinner->value()).toString();
}

void BorderDialog::onTypeChanged() {
    type = borderTypes->currentText();
}

void BorderDialog::onClose() {
    QString border = "border:";
    border+=color+",";
    border+=width+",";
    border+=type;
    TabWidget::currentWidget()->currentCell()->setData(Qt::UserRole,QVariant(border));

    this->close();
}
