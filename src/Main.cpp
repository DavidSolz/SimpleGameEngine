
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <vector>
#include <stdio.h>

#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

#include "Vector2.h"
#include "Vector3.h"

#include "WadReader.h"

int width=640;
int height=480;

double offset = 0.01f;

float zoomLevel = 1.0f;
float scrollSpeed = 0.1f;

double mouseX = 0, mouseY = 0;

std::vector<Vector2> points;

void DrawLines();
void DrawPoints();
void UpdateProjectionMatrix();

static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

int main(int argc, char *argv[]){

    WadReader reader("ACHERON.WAD");

    reader.ReadChunks();

    // if(!glfwInit()){
    //     printf("Cannot initialize GLFW\n");
    //     return -1;
    // }

    // GLFWwindow *window = glfwCreateWindow(width, height, "Title", NULL, NULL);

    // if(!window){
    //     glfwTerminate();
    //     printf("Cannot create GLFW window\n");
    //     return -1;
    // }

    // const GLubyte *vendor = glGetString(GL_VENDOR);
    // const GLubyte *renderer = glGetString(GL_RENDERER);

    // printf("Vendor : %s\n", vendor);
    // printf("Device : %s\n", renderer);

    // glfwMakeContextCurrent(window);
    // glfwSwapInterval(1); //wlacz v-sync

    // glfwSetCursorPosCallback(window, cursorPositionCallback);
    // glfwSetMouseButtonCallback(window, mouseButtonCallback);


    // while(!glfwWindowShouldClose(window)){

    //     glClear(GL_COLOR_BUFFER_BIT);

    //     glfwGetWindowSize(window , &width, &height);
    //     glViewport(0, 0, width, height);

    //     DrawPoints();
    //     DrawLines();

    //     glfwSwapBuffers(window);
    //     glfwPollEvents();
    // }

    // glfwDestroyWindow(window);

    // glfwTerminate();

    return 0;
}

void DrawPoints(){

    glPointSize(5);
    glColor3f(1,0,0);

    glBegin(GL_POINTS);

    for(auto &element : points){
        glVertex2f(element.x, element.y);
    }

    glEnd();
}


void DrawLines(){

    glColor3f(0xFF,0xFF,0xFF);


    glBegin(GL_LINE_LOOP);

    for(int i=1 ; i < points.size(); i++){

        glVertex2f(points[i-1].x, points[i-1].y);
        glVertex2f(points[i].x, points[i].y);
    
    }

    glEnd();

}


static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos){

    double normalizedX = (2.0 * xpos / width) - 1.0;
    double normalizedY = 1.0 - (2.0 * ypos / height);

    mouseX = normalizedX;
    mouseY = normalizedY;

}

bool isDrawing = false;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if(action!=GLFW_PRESS)
        return;

    if (button == GLFW_MOUSE_BUTTON_LEFT) {

        if(!isDrawing){
            points.push_back(Vector2(mouseX, mouseY));
            isDrawing = true;
        }else{
            points.push_back( Vector2(mouseX, mouseY));
            isDrawing = false;
        }


    }else if(button == GLFW_MOUSE_BUTTON_RIGHT){
        points.clear();
    }
}
