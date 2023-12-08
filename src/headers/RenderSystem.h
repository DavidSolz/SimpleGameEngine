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
#include "IUpdateable.h"
#include "Transform.h"
#include "Color.h"
#include "Entity.h"
#include "Timer.h"

#define test_width 5
#define test_height 5

#define GRID_VIEW

class RenderSystem : public IUpdateable{

public:

    void SetEntityManager(EntityManager *_entityManager){
        this->entityManager = _entityManager;
    }

    void Update() {

        timer->TicTac();

        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_QUADS);
            for (Entity* entity : entityManager->GetAllEntities()) {
                Transform* transform = entity->GetComponent<Transform>();
                Color* color = entity->GetComponent<Color>();

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
        fprintf(stdout, "Releasing resources.\n");
        glfwDestroyWindow(window);
        glfwTerminate();
    }

private:
    EntityManager * entityManager;
    GLFWwindow * window;
    Timer * timer;
};


#endif
