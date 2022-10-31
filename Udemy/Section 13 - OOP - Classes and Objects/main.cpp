#include <iostream>
#include <vector>

// Coding Exercise 29, 30, 31
#include "Deep.h"
#include "Display.h"
#include "Dog.h"
#include "Entity.h"
#include "Move.h"
#include "Shallow.h"

void print_num_entities()
{
    std::cout << "Active entities: "<< Entity::get_num_entities() << std::endl;
}

void display_entity(const Entity &entity)
{
    std::cout << "Name: " << entity.name << std::endl;
    std::cout << "Health: " << entity.health << std::endl;
    std::cout << "XP: " << entity.xp << std::endl;
}

int main()
{
    {
        Dog dog {"Satan", 666};
        std::cout << dog.get_name() << " is " << dog.get_age() << " years old." << std::endl;

        Dog another_dog {dog};
        another_dog.set_name("Copy of " + dog.get_name());
    }

    Dog *dog {nullptr};

    dog = new Dog();

    dog->set_name("Snoop");
    dog->set_age(60);

    std::cout << "The dogs name is " << dog->get_name() << std::endl;
    std::cout << dog->get_name() << " is " << dog->get_age() << " years old." << std::endl;
    std::cout << "Though in human years " << dog->get_name() << " is " << dog->get_human_years() << " years old.." << std::endl;
    dog->speak();

    delete dog;

    // Copy
    {
        // Shallow copy of object with raw pointer will crash! Avoid!
        /*Shallow shallow {99};
        Shallow copy_of_shallow {shallow};
        copy_of_shallow.set_data(98);
        shallow.print();
        copy_of_shallow.print();*/

        Deep deep {99};
        Deep copy_of_deep {deep};
        copy_of_deep.set_data(98);
        deep.print();
        copy_of_deep.print();
    }

    // Move
    {
        std::cout << std::endl;
        std::vector<Move> vector;

        // Move constructor will be called for temp r-values
        // Very efficient!
        vector.push_back(Move{10});
        vector.push_back(Move{20});
    }

    // Static
    {
        std::cout << std::endl;
        print_num_entities();
        Entity voidar {"Voidar"};
        display_entity(voidar);

        // Friend class of Entity
        Display::display_entity(voidar);
        print_num_entities();

    }
    print_num_entities();

    return 0;
}