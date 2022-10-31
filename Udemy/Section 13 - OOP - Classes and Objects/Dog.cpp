#include <iostream>
#include "Dog.h"

// Default constructor with delegated constructor initializer list
Dog::Dog(std::string name, int age)
    : name{name}, age{age}
{
    std::cout << this->name << " lives!" << std::endl;
}

// Copy constructor with initializer list
Dog::Dog(const Dog &source)
    : name{source.name}, age{source.age}
{
    std::cout << source.name << " was copied." << std::endl;
}

void Dog::set_name(std::string name)
{
    this->name = name;
}

std::string Dog::get_name() const
{
    return this->name;
}

void Dog::set_age(int age)
{
    this->age = age;
}

int Dog::get_age() const
{
    return this->age;
}

int Dog::get_human_years() const
{
    return this->age * 7;
}

void Dog::speak()
{
    std::cout << "Woof!" << std::endl;
}

Dog::~Dog()
{
    //delete this->pointer;
    std::cout << this->name << " has died." << std::endl;
}

