#include <QMenu>
#include <QAction>
#include <QColorDialog>

#include "homebar.hh"
#include "tabwidget.hh"

HomeBar::HomeBar()
    : cellColor(new QToolButton)
{
    QMenu *colorMenu = new QMenu;
    QAction *bg = new QAction("Background",colorMenu);
    QAction *fg = new QAction("Text",colorMenu);
    colorMenu->addAction(bg);
    colorMenu->addAction(fg);

    cellColor->setPopupMode(QToolButton::InstantPopup);
    cellColor->setMenu(colorMenu);
    cellColor->setText("Color");

    this->addWidget(cellColor);

    connect(bg,&QAction::triggered,this,&HomeBar::onBgColorClicked);
    connect(fg,&QAction::triggered,this,&HomeBar::onFgColorClicked);
}

HomeBar::~HomeBar() {
    delete cellColor;
}

void HomeBar::onBgColorClicked() {
    QColor color = QColorDialog::getColor();
    TabWidget::currentWidget()->currentCell()->setBackgroundColor(color);
}

void HomeBar::onFgColorClicked() {
    QColor color = QColorDialog::getColor(Qt::black);
    TabWidget::currentWidget()->currentCell()->setTextColor(color);
}
