#include "ribbon.hh"

Ribbon::Ribbon()
    : fileBar(new MainToolbar),
      cellBar(new CellBar)
{
    this->addTab(fileBar,"File");
    this->addTab(cellBar,"Cells");
}

Ribbon::~Ribbon() {
    delete fileBar;
    delete cellBar;
}
