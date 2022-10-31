#pragma once
#include <iostream>
#include "Entity.h"

class Display
{
public:
    static void display_entity(const Entity &entity)
    {
        std::cout << "Name: " << entity.name << std::endl;
        std::cout << "Health: " << entity.health << std::endl;
        std::cout << "XP: " << entity.xp << std::endl;
    }
};