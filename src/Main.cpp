
#include "RenderSystem.h"
#include "Timer.h"

const uint32_t width = 640;
const uint32_t height = 480;

float Rand(uint32_t& seed){

    seed ^= (seed>>16);
    seed *= 0x85ebca6b;
    seed ^= (seed>>13);
    seed *= 0xc2b2ae35;
    seed ^= (seed>>16);

    return seed/(float)UINT32_MAX;
}

int main(int argc, char *argv[]){

    EntityManager entityManager;
    RenderSystem renderSystem;
    ComponentRegister componentManager;

    if(!renderSystem.Initialize(width, height, true))
        return -1;

    renderSystem.SetEntityManager(&entityManager);
    renderSystem.SetComponentRegister(&componentManager);

    uint32_t seed = glfwGetTime() * UINT32_MAX;

    std::vector<IUpdateable*> systems;

    systems.push_back(&renderSystem);

    

    float radius = 20.0f;

    auto &transforms = componentManager.GetComponentMap<Transform>();

    while(renderSystem.ShouldClose()){

        for(IUpdateable* subsystem : systems){
            subsystem->Update();
        }

    Vector3 position;

    position.x = (2*Rand(seed)-1)*width/2.0f + width/2.0f;
    position.y = (2*Rand(seed)-1)*height/2.0f + height/2.0f;

    bool allowed = true;

    for(const EntityId id : entityManager.GetAllEntities()){

        Transform * transform = static_cast<Transform*>(transforms[id]);

        if(!transform)
            continue;

        Vector3 diff = position - transform->position;

        if ( Vector3::Dot(diff, diff) <= radius * radius ){
            allowed = false;
            break;
        }

    }

    if(allowed){
        EntityId id = entityManager.CreateEntity();
        Transform * transform = componentManager.AddComponent<Transform>(id);
        transform->position = position;
    }

    }

    return 0;
}
