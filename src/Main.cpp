
#include "RenderSystem.h"
#include "Timer.h"
#include <stdlib.h>
#include <time.h>

const int width = 640;
const int height = 480;


int main(int argc, char *argv[]){

    srand(time(NULL));

    EntityManager entityManager;

    RenderSystem renderSystem;

    for(int i=0 ;i < 100 ; i++){
        Entity* e1 = entityManager.CreateEntity();
        Transform* t = e1->AddComponent<Transform>();
        float xPos = width/2.0f + (rand()/(float)RAND_MAX*10 -5)*30;
        float yPos = height/2.0f + (rand()/(float)RAND_MAX*10 -5)*30;
        t->position = Vector3(xPos, yPos);
    }

    if(!renderSystem.Initialize(width, height))
        return -1;

    GLFWwindow * window = renderSystem.GetWindow();

    Timer* timer = Timer::GetInstance();

    while(!glfwWindowShouldClose(window)){

        timer->TicTac();
        renderSystem.Update(entityManager);

        for(Entity *entity : entityManager.GetAllEntities()){
            Transform* tr = entity->GetComponent<Transform>();
            tr->position.x+=1.0f;
        }

    }

    return 0;
}
