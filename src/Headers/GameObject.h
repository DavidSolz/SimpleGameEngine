#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ComponentRegister.h"
#include "Vector3.h"
#include <string>

class GameObject {

public:

GameObject();
GameObject(const std::string& _name);

template<typename T>
void AddComponent();

template<typename T>
void GetComponent();

template<typename T>
void GetEntitiesWithComponent();

private:
    EntityId id;
    std::string name;
};

#endif