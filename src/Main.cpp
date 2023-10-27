
#include <stdlib.h>
#include <stdio.h>
#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif


int width=640, height=480;
int framebufferWidth, framebufferHeight;

float moveSpeed = 0.02f;

#include "QuadTree.h"
#include <GLFW/glfw3.h>

QuadTree *tree;

void WindowResizeCallback(GLFWwindow *window, int w, int h);
void WindowMouseCallback(GLFWwindow *window, int button, int action, int mods);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(int argc, char *argv[]){

    tree = new QuadTree(2.0f, 2.0f);

    if(!glfwInit()){
        printf("Cannot initialize GLFW\n");
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(width, height, "Title", NULL, NULL);

    if(!window){
        glfwTerminate();
        printf("Cannot create GLFW window\n");
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); //wlacz v-sync

    const GLubyte *vendor = glGetString(GL_VENDOR);
    const GLubyte *renderer = glGetString(GL_RENDERER);

    printf("Vendor : %s\n", vendor);
    printf("Device : %s\n", renderer);
    
    glfwSetWindowSizeCallback(window, WindowResizeCallback);
    glfwSetMouseButtonCallback(window, WindowMouseCallback);
    glfwSetKeyCallback(window, KeyCallback);

    std::list<Vector2> points;

    while(!glfwWindowShouldClose(window)){

        glClear(GL_COLOR_BUFFER_BIT);

        tree->GetAllObjects(points);

        glPointSize(5.0f);

        glBegin(GL_POINTS);
            for(auto const point : points){
                glVertex2f(point.x, point.y);
            }
        glEnd();

        points.clear();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete tree;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void WindowResizeCallback(GLFWwindow *window, int w, int h){

    width = w;
    height = h;

    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);
}

void WindowMouseCallback(GLFWwindow *window, int button, int action, int mods){

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // Calculate the world coordinates of the point relative to the camera position and zoom level.
    double worldX = (2.0f * xpos) / width - 1.0f;
    double worldY = 1.0f - (2.0f *ypos ) / height;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS){
        Vector2 point(worldX, worldY);
        tree->InsertObject(point);
    }
    
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS){
        tree->Clean();
    }
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        // Adjust camera position based on key presses
        if (key == GLFW_KEY_ESCAPE){
            glfwSetWindowShouldClose(window, true);
        }
    }
}