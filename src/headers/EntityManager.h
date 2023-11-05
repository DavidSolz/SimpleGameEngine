#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"
#include <vector>

class EntityManager{

public:

    Entity CreateEntity(){
        EntityId id = nextEntityId++;
        Entity entity(id);
        entities.push_back(entity);
        return entity;
    }

    std::vector<Entity> entities;
private:
    EntityId nextEntityId = 1;
};




#endif