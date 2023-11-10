#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <stdio.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "EntityManager.h"
#include "Transform.h"
#include "Entity.h"
#include "Timer.h"

#define test_width 5
#define test_height 5

class RenderSystem{

public:

    void Update(EntityManager& entityManager) {

        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_QUADS);
            for (Entity* entity : entityManager.GetAllEntities()) {
                Transform* transform = entity->GetComponent<Transform>();

                if (!transform)
                        continue;

                glVertex2f(transform->position.x - test_width, transform->position.y - test_height);
                glVertex2f(transform->position.x + test_width, transform->position.y - test_height);
                glVertex2f(transform->position.x + test_width, transform->position.y + test_height);
                glVertex2f(transform->position.x - test_width, transform->position.y + test_height);
            }
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    bool Initialize(const int & width, const int &height){
        
        if(!glfwInit()){
            printf("Cannot create initialize GLFW.\n");
        }
        
        window = glfwCreateWindow(width, height, "Window", NULL, NULL);

        if(!window){
            glfwTerminate();
            printf("Cannot create GLFW window.\n");
            return false;
        }

        glfwMakeContextCurrent(window);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwSwapInterval(1);

        glOrtho(0, width, 0, height, -1.0f, 1.0f);
        if (glewInit() != GLEW_OK) {
            glfwDestroyWindow(window);
            glfwTerminate();
            fprintf(stderr, "Failed to initialize GLEW\n");
            return false;
        }

        timer = Timer::GetInstance();

        return true;
    }

    GLFWwindow * GetWindow(){
        return window;
    }

    ~RenderSystem(){
        fprintf(stdout, "Releasing resources.\n");
        glfwDestroyWindow(window);
        glfwTerminate();
    }

private:
    GLFWwindow * window;
    Timer * timer;
};


#endif