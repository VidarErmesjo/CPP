#pragma once
#include <iostream>
#include <string>

class Entity
{
private:
    static int num_entities;

    friend void display_entity(const Entity &entity);
    friend class Display;

    std::string name;
    int health;
    int xp;

public:
    static int get_num_entities();

    std::string get_name() const { return name; }
    int get_health() const { return health; }
    int get_xp() const { return xp; }
    void set_name(std::string name) { this->name = name; }
    void set_health(int health) { this->health = health; }
    void set_xp(int xp) { this->xp = xp; }

    Entity(std::string name = "None", int health = 100, int xp = 0);
    Entity(const Entity &source);
    ~Entity();
};