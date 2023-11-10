#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <stdio.h>
#include <unordered_map>
#include <typeinfo>

class GameObject
{

public:
    template<typename T>
    T* AddComponent(){
        if(components.find(typeid(T).hash_code())!=components.end()){
            fprintf(stderr, "GameObject already contains component of that type.\n");
            return NULL;
        }
        T* component = new T();
        components[typeid(T).hash_code()]= (void*)component;
        return component;
    }

    //It does not work, why ?
    template<typename T>
    T* AddComponent(T&& component){
        components[typeid(T).hash_code()] = (void*)&component;
        return component;
    }

    template<typename T>
    void RemoveComponent(){
        auto it = components.find(typeid(T).hash_code());
        if(it!=components.end()){
            components.erase(typeid(T).hash_code());
        }
    }

    template<typename T>
    T* GetComponent(){
        auto it = components.find(typeid(T).hash_code());
        if (it != components.end()) {
            return static_cast<T*>(it->second);
        }
        return nullptr;
    }


private:
    std::unordered_map<size_t, void*> components;
};


#endif