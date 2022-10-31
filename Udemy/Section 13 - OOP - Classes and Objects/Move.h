#pragma once

#include <iostream>

class Move
{
private:
    int *data;
public:
    void set_data(int data) { *this->data = data; }
    int get_data() const { return *this->data; }
    void print() const { std::cout << *data << std::endl; }

    // Constructor
    Move(int data);

    // Copy constructor
    Move(const Move &source);

    // Move constructor
    Move(Move &&source) noexcept;

    // Destructor
    ~Move();
};