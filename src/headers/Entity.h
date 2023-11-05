#ifndef ENTITY_H
#define ENTITY_H

using EntityId = unsigned int;

struct Entity{

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