#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "EntityManager.h"
#include "ComponentManager.h"
#include <stdio.h>
#include "Transform.h"
#include "Entity.h"

class RenderSystem{

public:

    void Update(EntityManager& entityManager, ComponentManager& componentManager) {
        for (Entity& entity : entityManager.entities) {
            auto transform = componentManager.GetComponent<Transform>(entity.GetEntityId());

            if (transform) {
                fprintf(stdout, "{%d} Position : %f %f\n", entity.GetEntityId(), transform->position.x, transform->position.y);
            }
        }
    }
};


#endif