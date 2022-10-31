#pragma once

#include <iostream>

class Deep
{
private:
    int *data;
public:
    void set_data(int data) { *this->data = data; }
    int get_data() const { return *this->data; }
    void print() const { std::cout << *data << std::endl; }
    Deep(int data);
    Deep(const Deep &source);
    ~Deep();
};