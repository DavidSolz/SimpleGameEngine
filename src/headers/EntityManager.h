#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"
#include <vector>

class EntityManager{

public:

    Entity* CreateEntity(){
        EntityId id = nextEntityId++;
        Entity* entity = new Entity(id);
        entities.push_back(entity);
        return entity;
    }

    ~EntityManager(){
        for(Entity* entity : entities){
            if(entity)
                delete entity;
        }
    }

    std::vector<Entity*> entities;
private:
    EntityId nextEntityId = 1;
};




#endif