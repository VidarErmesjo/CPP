#pragma once

#include <iostream>

class IPrintable
{
    friend std::ostream &operator<<(std::ostream &os, const IPrintable &obj);
public:
    virtual void print(std::ostream &os) const = 0;
};

std::ostream &operator<<(std::ostream &os, const IPrintable &obj)
{
    obj.print(os);
    return os;
}