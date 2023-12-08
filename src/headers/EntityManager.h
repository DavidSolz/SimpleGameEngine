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

    std::vector<Entity*> GetAllEntities() const{
        return entities;
    }

    ~EntityManager(){
        for(Entity* entity : entities){
            if(entity)
                delete entity;
        }
    }

private:
    std::vector<Entity*> entities;
    EntityId nextEntityId = 1;
};




#endif
