#include <iostream>
#include "Deep.h"

Deep::Deep(int data)
{
    this->data = new int;
    *this->data = data;
}

// Deep copy with delegation
Deep::Deep(const Deep &source)
    : Deep{*source.data}
{
    //this->data = new int;
    //*this->data = *source.data;
    std::cout << "Copy constructor - deep copy" << std::endl;
}

Deep::~Deep()
{
    delete data;
    std::cout << "Destructor - freeing data" << std::endl;
}