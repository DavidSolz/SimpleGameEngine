
#include "RenderSystem.h"
#include "Timer.h"
#include <stdlib.h>
#include <time.h>

const uint32_t width = 640;
const uint32_t height = 480;

int main(int argc, char *argv[]){

    srand(time(NULL));

    EntityManager entityManager;

    RenderSystem renderSystem;

    if(!renderSystem.Initialize(width, height, true))
        return -1;

    renderSystem.SetEntityManager(&entityManager);

    std::vector<IUpdateable*> systems;

    systems.push_back(&renderSystem);

    for(int i=0 ; i < 100 ; i++){

        Entity* entity = entityManager.CreateEntity();
        Transform* transform = entity->AddComponent<Transform>();
        Color* color = entity->AddComponent<Color>();

        float xPos = width/2.0f + (rand()/(float)RAND_MAX*10 -5)*30;
        float yPos = height/2.0f + (rand()/(float)RAND_MAX*10 -5)*30;
        transform->position = Vector3(xPos, yPos);

        color->R = rand()/(float)RAND_MAX;
        color->G = rand()/(float)RAND_MAX;
        color->B = rand()/(float)RAND_MAX;

    }

    while(renderSystem.ShouldClose()){

        for(IUpdateable* subsystem : systems){
            subsystem->Update();
        }

    }

    return 0;
}
