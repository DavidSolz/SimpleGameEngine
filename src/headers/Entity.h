#ifndef ENTITY_H
#define ENTITY_H

#include "GameObject.h"

using EntityId = uint32_t;

class Entity : public GameObject{

public:

    Entity(const EntityId& _entityId){
        this->entityID = _entityId;
    }

    EntityId GetEntityId(){
        return entityID;
    }

private:
    EntityId entityID;
};

#endif
