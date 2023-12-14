
#include "RenderSystem.h"
#include "Timer.h"
#include "BST.h"

#include <queue>

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

    RenderSystem renderSystem;
    ComponentRegister componentManager;

    if(!renderSystem.Initialize(width, height, true))
        return -1;

    renderSystem.SetComponentRegister(&componentManager);

    uint32_t seed = (uint32_t)(glfwGetTime()*UINT32_MAX);

    while(renderSystem.ShouldClose()){

        renderSystem.Update();


    }

    return 0;
}
