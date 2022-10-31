#include <cstring>
#include <iostream>
#include <vector>
#include "String.h"

// Global Binary Equal operator overload
bool operator==(const String &lhs, const String &rhs)
{
    return (std::strcmp(lhs.string, rhs.string) == 0);
}

// Global stream insertion and extraction operator overload
std::ostream &operator<<(std::ostream &output, const String &object)
{
    //return output << object.get_string(); // If not friend
    return output << object.string;
}

std::istream &operator>>(std::istream &input, String &object)
{
    char *buffer = new char[1000];
    input >> buffer;
    object = String {buffer};
    delete [] buffer;

    return input;
}

int main()
{
    String empty;             // No arguments constructor
    String larry {"Larry"};   // Overloaded constructor
    String stooge {larry};    // Copy constructor

    {
        String moe {"Moe"};
        moe.display();
        stooge.display();
        stooge = moe;
    }

    empty = "Hello";

    empty.display();
    larry.display();
    stooge.display();

    std::cout << std::endl;

    std::vector<String> vector;

    vector.push_back(String{"Larry"});
    vector.push_back(String{"Moe"});
    vector.push_back(String{"Curly"});

    // Concatenation and move assignment
    vector.push_back(String{"Larry"} + String{" Moe"} + String{" and Curly"});

    for (const auto &string : vector)
        string.display();

    for (auto &string : vector)
        string = "Changed";

    for (const auto &string : vector)
        string.display();

    std::cout << std::endl;
    String larry1 {"LARRY"};
    String larry2;

    // To lower case
    larry2 = -larry1;
    
    larry1.display();
    larry2.display();

    std::cout << std::boolalpha;
    std::cout << "Equals: " << (larry1 == larry2) << std::endl;

    larry1 = larry2;
    larry1.display();
    larry2.display();
    std::cout << "Equals: " << (larry1 == larry2) << std::endl;

    String voidar {"Voidar"};

    // Output stream operator global overload
    std::cout << voidar << std::endl;
    std::cout << "Enter string (1000 max characters): " << std::endl;
    std::cin >> voidar;
    std::cout << "You entered: " << voidar << std::endl;

    return 0;
}