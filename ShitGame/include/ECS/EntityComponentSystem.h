#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentId = std::size_t;
using Group = std::size_t;

inline ComponentId getNewComponentTypeId()
{
    static ComponentId lastId = 0u;
    return lastId++;
}

template<typename T> inline ComponentId getComponentTypeId() noexcept
{
    //static_assert (std::is_base_of<Component, T)>::value, "");
    static ComponentId typeId = getNewComponentTypeId();
    return typeId;
}

class Component
{
public:
    Entity* entity;

    virtual ~Component() {}

    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}
};

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

class Entity
{
    Manager &manager;
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;
    
    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;

public:
    Entity(Manager &manager)
    :   manager(manager)
    {}

    void update()
    {
        for(auto& component : components)
            component->update();
    }

    void draw()
    {
        for(auto& component : components)
            component->draw();
    }
    
    bool isActive() const { return active; }
    void destroy() { active = false; }

    bool hasGroup(Group group) { return groupBitSet[group]; }

    void addGroup(Group group);
    void deleteGroup(Group group) { groupBitSet[group] = false; }

    template<typename T> bool hasComponent() const
    {
        return componentBitSet[getComponentTypeId<T>()];
    }

    template<typename T, typename... A>
    T& addComponents(A&&... args)
    {
        T* component(new T(std::forward<A>(args)...));
        component->entity = this;
        std::unique_ptr<Component> uniquePtr { component };
        components.emplace_back(std::move(uniquePtr));

        componentArray[getComponentTypeId<T>()] = component;
        componentBitSet[getComponentTypeId<T>()] = true;

        component->init();
        
        return *component;
    }

    template<typename T> T& getComponent() const
    {
        auto ptr(componentArray[getComponentTypeId<T>()]);
        return *static_cast<T*>(ptr);
    }
};

class Manager
{
    std::vector<std::unique_ptr<Entity>> entities;   
    std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
    void update()
    {
        for(auto& entity : entities)
            entity->update();
    }

    void draw()
    {
        for(auto& entity : entities)
            entity->draw();
    }

    void refresh()
    {
        for(auto i(0u); i < maxGroups; i++)
        {
            auto &vector(groupedEntities[i]);
            vector.erase(std::remove_if(std::begin(vector), std::end(vector),
                    [i](Entity *entity)
                    {
                        return !entity->isActive() || !entity->hasGroup(i);
                    }), std::end(vector));
        }

        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity> &entity)
            {
                return !entity->isActive();
            }), std::end(entities));        
    }

    void addToGroup(Entity *entity, Group group) { groupedEntities[group].emplace_back(entity); }
    
    std::vector<Entity*> &getGroup(Group group) { return groupedEntities[group]; }

    Entity& addEntity()
    {
        Entity *entity = new Entity(*this);
        std::unique_ptr<Entity> uniquePtr { entity };
        entities.emplace_back(std::move(uniquePtr));

        return *entity;
    }
};