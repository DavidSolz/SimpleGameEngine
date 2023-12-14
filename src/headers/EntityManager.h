#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <list>
#include <algorithm>
#include <stdint.h>

using EntityId = uint32_t;

class EntityManager{

public:

    EntityId CreateEntity();

    std::list<EntityId> GetAllEntities() const;

    void RemoveEntity(const EntityId & _entityId);

    static EntityManager* GetInstance();

    ~EntityManager();

private:

    EntityManager();

    std::list<EntityId> entities;
    std::list<EntityId> queue;
    EntityId nextEntityId = 0;
};


#endif
