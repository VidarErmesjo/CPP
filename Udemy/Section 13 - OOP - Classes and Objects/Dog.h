#pragma once

#include <string>

class Dog
{
private:
    std::string name;
    int age;
public:
    Dog(std::string name = "Dog", int age = 0);
    Dog(const Dog &source);
    void set_name(std::string name);
    std::string get_name() const;
    void set_age(int age);
    int get_age() const;
    int get_human_years() const;
    void speak();
    ~Dog();
};