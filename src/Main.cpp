
#include "RenderSystem.h"

const int width = 640;
const int height = 480;


int main(int argc, char *argv[]){

    EntityManager entityManager;

    RenderSystem renderSystem;

    Entity* e1 = entityManager.CreateEntity();
    Transform* t = e1->AddComponent<Transform>();

    t->position = Vector3(width/2.0f, height/2.0f);

    if(!renderSystem.Initialize(width, height))
        return -1;

    GLFWwindow * window = renderSystem.GetWindow();

    while(!glfwWindowShouldClose(window)){

        renderSystem.Update(entityManager);

    }

    return 0;
}
