#include "Collision.h"
#include "ECS/Components.h"

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
    if((rectA.x + rectA.w >= rectB.x) && (rectB.x + rectB.w >= rectA.x) && (rectA.y + rectA.h >= rectB.y) && (rectB.y + rectB.h >= rectA.y))
        return true;

    return false;
}

bool Collision::AABB(const ColliderComponent& colliderA, const ColliderComponent& colliderB)
{
    if(AABB(colliderA.collider, colliderB.collider))
    {
        if(colliderA.tag == colliderB.tag)
            return false;
            
        std::cout << colliderA.tag << " hit: " << colliderB.tag << std::endl;
        return true;
    }
    else
    {
        return false;
    }    
}