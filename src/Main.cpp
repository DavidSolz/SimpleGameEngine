
#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif


int width=640, height=480;
int framebufferWidth, framebufferHeight;

float moveSpeed = 0.2f;

#include "QuadTree.h"
#include "Camera.h"

Camera camera;

QuadTree *tree;

void WindowResizeCallback(GLFWwindow *window, int w, int h);
void WindowMouseCallback(GLFWwindow *window, int button, int action, int mods);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
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

    glfwSetScrollCallback(window, ScrollCallback);
    glfwSetKeyCallback(window, KeyCallback);

    camera = Camera(window, width, height);

    while(!glfwWindowShouldClose(window)){

        glClear(GL_COLOR_BUFFER_BIT);

        camera.updateProjectionMatrix();
        camera.SetWorldBounds(width, height);
        tree->Draw();

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

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    // Adjust the camera's zoom based on scroll direction
    if (yoffset > 0) {
        camera.AdjustZoom(1.1f); // Increase zoom
    } else if (yoffset < 0) {
        camera.AdjustZoom(0.9f); // Decrease zoom
    }
    camera.updateProjectionMatrix();
}

void WindowMouseCallback(GLFWwindow *window, int button, int action, int mods){

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // Calculate the world coordinates of the point relative to the camera position and zoom level.
    double worldX = camera.position.x + (xpos - camera.worldBound.width / 2.0) / camera.zoom;
    double worldY = camera.position.y - (ypos - camera.worldBound.height / 2.0) / camera.zoom;

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
        if (key == GLFW_KEY_W) {
            camera.Move(0.0, moveSpeed); // Move up (positive Y-axis)
        } else if (key == GLFW_KEY_S) {
            camera.Move(0.0, -moveSpeed); // Move down (negative Y-axis)
        } else if (key == GLFW_KEY_A) {
            camera.Move(-moveSpeed, 0.0); // Move left (negative X-axis)
        } else if (key == GLFW_KEY_D) {
            camera.Move(moveSpeed, 0.0); // Move right (positive X-axis)
        }
    }
}