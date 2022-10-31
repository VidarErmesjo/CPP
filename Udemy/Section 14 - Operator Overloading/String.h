#pragma once
#include <ostream>

class String
{
private:
    char *string;   // Pointer to a char[] that holds a C-style string

public:

    String();                                   // No arguments constructor
    String(const char *string);                 // Overloaded constructor
    String(const String &source);               // Copy constructor
    String(String &&source);                    // Move constructor
    ~String();                                  // Destructor
    String &operator=(const String &rhs);       // Copy assignment
    String &operator=(String &&rhs);            // Move assignment
    String operator-() const;                   // Unary Minus operator overload (make lower case)
    //bool operator==(const String &rhs) const;   // Binary Equals operator overload
    String operator+(const String &rhs) const;  // Binary Plus operator overload (concatenate)

    friend bool operator==(const String &lhs, const String &rhs);   // Binary Equals operator global overload
    friend std::ostream &operator<<(std::ostream &output, const String &object);    // Output stream global overload

    void display() const;
    int get_length() const;
    const char *get_string() const;
};