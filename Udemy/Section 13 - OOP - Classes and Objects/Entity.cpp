#include <string>
#include "Entity.h"

int Entity::num_entities {0};

// Constructor with initializer list
Entity::Entity(std::string name, int health, int xp)
    :   name{name}, health{health}, xp{xp}
{
    num_entities++;
}

// Copy constructor with delegate
Entity::Entity(const Entity &source)
    :   Entity{source.name, source.health, source.xp}
{
}

int Entity::get_num_entities()
{
    return num_entities;
}

Entity::~Entity()
{
    num_entities--;
}