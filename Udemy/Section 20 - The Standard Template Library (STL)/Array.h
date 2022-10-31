#pragma once
#include <iostream>

// Generic array
template <typename T, int N>
class Array
{
    int size {N};
    T values[N];

    friend std::ostream &operator<<(std::ostream &os, const Array<T, N> &arr)
    {
        os << "[ ";
        for (const auto &value : arr.values)
            os << value << " ";
        os << "]" << std::endl;
        return os;
    }

public:
    Array() = default;
    Array(T init_value) { for (auto &item : this->values) item = init_value; }

    T &operator[](int index) { return values[index]; }

    void fill(T value) { for (auto &item : this->values ) item = value; }
    int get_size() const { return this->size; };
};