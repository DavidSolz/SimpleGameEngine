
#include <stdio.h>

#include "RenderSystem.h"

int main(int argc, char *argv[]){

    EntityManager entityManager;
    ComponentManager componentManager;

    RenderSystem renderSystem;

    Entity e1 = entityManager.CreateEntity();
    Transform t={Vector3(1.0f,1.0f), Vector3(0.0f,0.0f)};
    componentManager.AddComponent(e1.GetEntityId(), t);

    Entity e2 = entityManager.CreateEntity();
    
    componentManager.AddComponent(e2.GetEntityId(), Transform());

    renderSystem.Update(entityManager, componentManager);

    return 0;
}
