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

#include "data_actions.hh"
#include "../tabwidget.hh"
#include "../sheetwidget.hh"
#include "../tablewidget.hh"

DataItem DataActions::clipboard1;
QVector<DataItem> DataActions::clipboard;

void DataActions::cut_data() {
    SheetWidget *sheet = TabWidget::currentWidget();

    if (sheet->currentTable()->currentSelectedItems().size()==1) {
        QTableWidgetItem *current = sheet->currentCell();
        clipboard1.item.x = current->column();
        clipboard1.item.y = current->row();
        clipboard1.item.data = current->text();

        clipboard1.original_col = current->column();
        clipboard1.original_row = current->row();
    } else {
        auto items = sheet->currentTable()->currentSelectedItems();
        for (int i = 0; i<items.size(); i++) {
            auto current = items.at(i);
            DataItem item;
            item.original_col = current.column();
            item.original_row = current.row();
            
            QTableWidgetItem *tb_item = sheet->currentTable()->item(current.row(),current.column());
            if (tb_item==nullptr) {
              item.item.data = "";
            } else {
              item.item.data = tb_item->text();  
            }
            
            clipboard.push_back(item);
        }
    }
}

void DataActions::paste_data() {
    QTableWidgetItem *current = TabWidget::currentWidget()->currentCell();
    if (clipboard.isEmpty()) {
        paste_single_item(current->row(),current->column());
    } else {
        int cx = current->column();
        int cy = current->row();
        
        std::cout << "CX: " << cx << std::endl;
        std::cout << "CY: " << cy << std::endl << std::endl;
        
        int diff_x = 0;
        int diff_y = 0;
        int last_x = -1;
        int last_y = -1;
        
        for (DataItem item : clipboard) {
          int ox = item.original_col;
          int oy = item.original_row;
          std::cout << "O: " << ox << " " << oy << std::endl;
          
          if (last_x != -1 && last_y != -1) {
              diff_x = ox-last_x;
              diff_y = oy-last_y;
              
              if (diff_x<0) {
                diff_x*=-1;
              }
              
              if (diff_y<0) {
                diff_y*=-1;
              }
          }
          
          int dest_x = cx+diff_x;
          int dest_y = cy+diff_y;
          
          last_x = ox;
          last_y = oy;
          
          //Sets the new item
          QTableWidgetItem *nitem = TabWidget::currentWidget()->currentTable()->item(dest_x,dest_y);
          if (nitem==nullptr) {
              nitem = new QTableWidgetItem;
          }
          nitem->setText(item.item.data);
          TabWidget::currentWidget()->currentTable()->setItem(dest_y,dest_x,nitem);
          
          //Erases the old item
          QTableWidgetItem *original = TabWidget::currentWidget()->currentTable()->item(oy,ox);
          if (original==nullptr) {
              original = new QTableWidgetItem;
          }
          original->setText("");
          TabWidget::currentWidget()->currentTable()->setItem(oy,ox,original);
          
          diff_x = 0;
          diff_y = 0;
        }
        
        clipboard.clear();
    }
}

void DataActions::paste_single_item(int dest_row, int dest_col) {
    TableWidget *current = TabWidget::currentWidget()->currentTable();
    QTableWidgetItem *item = current->item(dest_row,dest_col);
    if (item==nullptr) {
        item = new QTableWidgetItem;
    }

    item->setText(clipboard1.item.data);
    current->setItem(dest_row,dest_col,item);

    QTableWidgetItem *original = new QTableWidgetItem;
    current->setItem(clipboard1.original_row,clipboard1.original_col,original);
}
