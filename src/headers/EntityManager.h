#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <list>
#include "BST.h"

using EntityId = uint32_t;

class EntityManager{

public:

    EntityId CreateEntity();

    std::vector<EntityId> GetAllEntities();

    void RemoveEntity(const EntityId & _entityId);

    static EntityManager* GetInstance();

    ~EntityManager();

private:

    EntityManager();

    BST<EntityId> entities;
    std::list<EntityId> queue;
    EntityId nextEntityId = 0;
};


#endif
