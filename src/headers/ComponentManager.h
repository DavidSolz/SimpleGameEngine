#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <unordered_map>
#include <typeinfo>
#include <memory>
#include "Entity.h"

class ComponentManager{
public:

    template<typename T>
    void AddComponent(const EntityId & entityId, T&&component){
        components[typeid(T).hash_code()][entityId] = (void*)(&component);
    }

    template<typename T>
    void RemoveComponent(const EntityId & entityId){
        auto& componentMap = components[typeid(T).hash_code()];
        auto it =componentMap.find(entityId);
        if(it!=componentMap.end()){
            componentMap.erase(entityId);
        }
    }

    template<typename T>
    T* GetComponent(const EntityId & entityId){
        auto& componentMap = components[typeid(T).hash_code()];
        auto it = componentMap.find(entityId);
        if (it != componentMap.end()) {
            return static_cast<T*>(it->second);
        }
        return nullptr;
    }

private:
    std::unordered_map<size_t, std::unordered_map<EntityId, void*>> components;
};


#endif