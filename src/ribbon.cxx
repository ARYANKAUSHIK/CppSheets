#include "ribbon.hh"

Ribbon::Ribbon()
    : fileBar(new MainToolbar),
      homeBar(new HomeBar)
{
    this->addTab(fileBar,"File");
    this->addTab(homeBar,"Home");

    this->setCurrentIndex(1);
}

Ribbon::~Ribbon() {
    delete fileBar;
    delete homeBar;
}
