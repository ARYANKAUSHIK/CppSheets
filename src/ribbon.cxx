#include "ribbon.hh"

Ribbon::Ribbon()
    : fileBar(new MainToolbar)
{
    this->addTab(fileBar,"File");
}

Ribbon::~Ribbon() {
    delete fileBar;
}
