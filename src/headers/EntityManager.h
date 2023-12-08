#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <list>
#include <algorithm>

using EntityId = uint32_t;

class EntityManager{

public:

    EntityId CreateEntity(){

        EntityId id;

        if(queue.size()>0){
            id = queue.front();
            queue.pop_front();
        }else{
            id = nextEntityId++;
        }

        entities.push_back(id);
        return id;
    }

    std::list<EntityId> GetAllEntities() const{
        return entities;
    }

    void RemoveEntity(const EntityId & _entityId){

        auto it = std::find(entities.begin(), entities.end(), _entityId);

        if (it != entities.end()) {
            entities.erase(it);
            queue.push_back(_entityId);
        }

    }

private:
    std::list<EntityId> entities;
    std::list<EntityId> queue;
    EntityId nextEntityId = 1;
};




#endif
