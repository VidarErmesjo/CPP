#include <cstring>
#include <iostream>
#include "String.h"

// No arguments constructor
String::String()
    :   string{nullptr}
{
    string = new char[1];
    *string = '\0';
}

// Overloaded constructor
String::String(const char *string)
    :   string{nullptr}
{
    if (string == nullptr)
    {
        this->string = new char[1];
        *this->string = '\0';
    }
    else
    {
        this->string = new char[std::strlen(string) + 1];
        std::strcpy(this->string, string);
    }
}

// Copy constructor
String::String(const String &source)
    :   string{nullptr}
{
    this->string = new char[std::strlen(source.string) + 1];
    std::strcpy(this->string, source.string);
}

// Move constructor
String::String(String &&source)
    :   string{source.string}
{
    source.string = nullptr;
}

// Destructor
String::~String()
{
    delete[] string;
}

// Copy assignment
String &String::operator=(const String &rhs)
{
    if (this == &rhs)
        return *this;

    delete [] string;

    string = new char[std::strlen(rhs.string) + 1];
    std::strcpy(string, rhs.string);

    return *this;
}

// Move assignment (more efficient than copy assignment)
String &String::operator=(String &&rhs)
{
    // Return self if same object / address
    if (this == &rhs)
        return *this;

    // Free memory from self and steal pointer from right-hand-side
    delete [] string;
    string = rhs.string;

    // Null the right-hand-side pointer and return self
    rhs.string = nullptr;

    return *this;
}

// Unary Minus overload (in this case used as a to-lower-case function)
String String::operator-() const
{
    char *buffer = new char[std::strlen(string) + 1];
    std::strcpy(buffer, string);
    for (size_t i {0}; i < strlen(buffer); i++)
        buffer[i] = std::tolower(buffer[i]);
    
    String temp {buffer};
    delete[] buffer;

    return temp;
}

// Binary Equals overload
/*bool String::operator==(const String &rhs) const
{
    return (std::strcmp(string, rhs.string) == 0);
}*/

// Concatenation
String String::operator+(const String &rhs) const
{
    size_t buffer_size = std::strlen(string) + std::strlen(rhs.string) + 1;
    char *buffer = new char[buffer_size];
    std::strcpy(buffer, string);
    std::strcat(buffer, rhs.string);

    String temp {buffer};
    delete [] buffer;

    return temp;
}

void String::display() const
{
    std::cout << string << " : " << get_length() << std::endl;
}

int String::get_length() const
{
    return std::strlen(string);
}

const char *String::get_string() const
{
    return string;
}