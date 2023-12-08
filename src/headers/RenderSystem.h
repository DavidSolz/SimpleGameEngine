#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <stdio.h>

#ifdef __APPLE__

#include <OpenGL/gl.h>

#else

#include <GL/gl.h>

#endif

#include <GLFW/glfw3.h>

#include "EntityManager.h"
#include "ComponentRegister.h"
#include "IUpdateable.h"
#include "Transform.h"
#include "Color.h"
#include "Timer.h"

#define test_width 1
#define test_height 1

#define GRID_VIEW

class RenderSystem : public IUpdateable{

public:

    void SetEntityManager(EntityManager *_entityManager){
        this->entityManager = _entityManager;
    }

    void SetComponentRegister(ComponentRegister *_componentRegister){
        this->componentRegister = _componentRegister;
    }

    void Update() {

        timer->TicTac();

        auto &transforms = componentRegister->GetComponentMap<Transform>();
        auto &colors = componentRegister->GetComponentMap<Color>();

        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_QUADS);
            for (const EntityId id : entityManager->GetAllEntities()) {
                Transform * transform = static_cast<Transform*>(transforms[id]);
                Color * color = static_cast<Color*>(colors[id]);

                if (!transform)
                    continue;

                if(color)
                    glColor3f(color->R, color->G, color->B);

                glVertex2f(transform->position.x - test_width, transform->position.y - test_height);
                glVertex2f(transform->position.x + test_width, transform->position.y - test_height);
                glVertex2f(transform->position.x + test_width, transform->position.y + test_height);
                glVertex2f(transform->position.x - test_width, transform->position.y + test_height);
            }
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    bool Initialize(const int & width, const int &height, const bool enableVSync){

        if(!glfwInit()){
            printf("Cannot create initialize GLFW.\n");
        }

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        window = glfwCreateWindow(width, height, "Window", NULL, NULL);

        if(!window){
            glfwTerminate();
            printf("Cannot create GLFW window.\n");
            return false;
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(enableVSync);

        glOrtho(0, width, 0, height, -1.0f, 1.0f);

        timer = Timer::GetInstance();

        return true;
    }

    bool ShouldClose(){
        return !glfwWindowShouldClose(window);
    }

    ~RenderSystem(){
        fprintf(stdout, "Releasing resources.     \n");
        glfwDestroyWindow(window);
        glfwTerminate();
    }

private:
    EntityManager * entityManager;
    ComponentRegister * componentRegister;
    GLFWwindow * window;
    Timer * timer;
};


#endif
