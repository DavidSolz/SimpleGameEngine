#ifndef COMPONENT_REGISTER_H
#define COMPONENT_REGISTER_H

#include <stdint.h>
#include <typeinfo>
#include <unordered_map>
#include <memory>

using EntityId = uint32_t;

class ComponentRegister {

public:

    template<typename T>
    T* AddComponent(const EntityId& _entityId) {

        size_t code = typeid(T).hash_code();

        auto submap_it = components.find(code);

        if (submap_it == components.end())
            components[code] = std::unordered_map<EntityId, void*>();

        auto &submap = components[code];

        auto it = submap.find(_entityId);

        if (it != submap.end()) 
            return static_cast<T*>(it->second);

        T * component = new T();
        submap[_entityId] = static_cast<void*>(component);

        return component;
    }

    template<typename T>
    void RemoveComponent(const EntityId& _entityId) {
        auto it = components.find(typeid(T).hash_code());

        if (it == components.end())
            return;

        auto element = it->second.find(_entityId);

        if (element != it->second.end()){

            delete static_cast<T*>(element->second);
            it->second.erase(element);

        }

    }

    template<typename T>
    std::unordered_map<EntityId, T*>& GetComponentMap(){
        size_t code = typeid(T).hash_code();
        return reinterpret_cast<std::unordered_map<EntityId, T*>&>(components[code]);
    }

    template<typename T>
    T* GetComponent(const EntityId& _entityId) const {
        auto it = components.find(typeid(T).hash_code());
        if (it == components.end())
            return NULL;

        auto element = it->second.find(_entityId);

        if (element == it->second.end())
            return NULL;

        return static_cast<T*>(element->second);
    }

private:
    std::unordered_map<size_t, std::unordered_map<EntityId, void*>> components;
};

#endif
