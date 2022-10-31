#include <iostream>
#include "Shallow.h"

Shallow::Shallow(int data)
{
    this->data = new int;
    *this->data = data;
}

Shallow::Shallow(const Shallow &source)
   :    data{source.data}
{
    std::cout << "Copy constructor - shallow copy" << std::endl;
}

Shallow::~Shallow()
{
    delete data;
    std::cout << "Destructor - freeing data" << std::endl;
}