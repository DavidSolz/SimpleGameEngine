#ifndef ENTITY_H
#define ENTITY_H

class Entity{

    unsigned int entityID;

public:

    Entity(const unsigned int& _entityId){
        this->entityID = _entityId;
    }

    unsigned int GetEntityId(){
        return entityID;
    }

};

#endif