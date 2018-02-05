#include "statusbar.hh"

StatusBar::StatusBar()
    : pathLabel(new QLabel),
      savedLabel(new QLabel)
{
    pathLabel->setText("untitled");
    savedLabel->setText("Saved");

    this->addWidget(pathLabel);
    this->addPermanentWidget(savedLabel);
}

StatusBar::~StatusBar() {
    delete pathLabel;
    delete savedLabel;
}

void StatusBar::setPathLabel(QString label) {
    pathLabel->setText(label);
}

void StatusBar::setSavedLabel(bool saved) {
    if (saved) {
        savedLabel->setText("Saved");
    } else {
        savedLabel->setText("Not saved");
    }
}
