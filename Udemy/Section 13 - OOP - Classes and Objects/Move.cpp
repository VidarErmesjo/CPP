#include <iostream>
#include "Move.h"

Move::Move(int data)
{
    this->data = new int;
    *this->data = data;

    std::cout << "Constructor for: " << data << std::endl;
}

// Deep copy constructor with delegation
Move::Move(const Move &source)
    : Move{*source.data}
{
    std::cout << "Copy constructor - deep copy for: " << *this->data << std::endl;
}

// Move constructor
// 'Steal' the data and null out the source pointer
Move::Move(Move &&source) noexcept
    : data{source.data}
{
    source.data = nullptr;
    std::cout << "Move constructor - moving resource: " << *this->data << std::endl;
}

Move::~Move()
{
    if (data != nullptr)
    {
        std::cout << "Destructor - freeing data for: " << *this->data << std::endl;
    }
    else
    {
        std::cout << "Destructor - freeing data for nullptr" << std::endl;
    }
    delete data;
}