#pragma once

#include <iostream>

class Shallow
{
private:
    int *data;
public:
    void set_data(int data) { *this->data = data; }
    int get_data() const { return *this->data; }
    void print() const { std::cout << *data << std::endl; }
    Shallow(int data);
    Shallow(const Shallow &source);
    ~Shallow();
};