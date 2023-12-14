#include "EntityManager.h"

static EntityManager *instance;

EntityManager::EntityManager(){
    
}

EntityId EntityManager::CreateEntity(){

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

std::list<EntityId> EntityManager::GetAllEntities() const{
    return entities;
}

void EntityManager::RemoveEntity(const EntityId & _entityId){

        auto it = std::find(entities.begin(), entities.end(), _entityId);

        if (it != entities.end()) {
            entities.erase(it);
            queue.push_back(_entityId);
        }

}

EntityManager* EntityManager::GetInstance(){
    if(!instance)
        instance = new EntityManager();

    return instance;
}

EntityManager::~EntityManager(){
    delete instance;
}