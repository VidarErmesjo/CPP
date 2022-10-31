#include <iostream>
#include <string>

// Coding Exercise 19
void cpp_strings()
{
    std::string unformated_full_name {"StephenHawking"};
    std::string first_name {unformated_full_name, 0, 7};
    std::string last_name = unformated_full_name.substr(7, 7);
    std::string formated_full_name = first_name + last_name;

    formated_full_name.insert(7, " ");

    std::cout << formated_full_name << std::endl;
}

void reverse_me(const std::string &string)
{
    for (auto it = string.rbegin(); it != string.rend(); it++)
        std::cout << *it;
}

int main()
{
    cpp_strings();

    return 0;
}