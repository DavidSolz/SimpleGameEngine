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

    entities.AddElement(id);
    return id;
}

std::vector<EntityId> EntityManager::GetAllEntities(){
    return entities.GetAllElements();
}

void EntityManager::RemoveEntity(const EntityId & _entityId){

        EntityId * it = entities.FindElement(_entityId);

        if (it != NULL) {
            entities.DeleteElement(_entityId);
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