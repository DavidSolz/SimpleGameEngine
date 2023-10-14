
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>

#include <vector>

#include "headers/Vectors.h"

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
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

int main(){


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

    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetScrollCallback(window, scrollCallback);


    while(!glfwWindowShouldClose(window)){

        glClear(GL_COLOR_BUFFER_BIT);

        glfwGetWindowSize(window , &width, &height);
        glViewport(0, 0, width, height);

        UpdateProjectionMatrix();
        DrawPoints();
        DrawLines();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

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

void UpdateProjectionMatrix() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-zoomLevel, zoomLevel, -zoomLevel, zoomLevel, 0, 1);
    glMatrixMode(GL_MODELVIEW);
}


void DrawLines(){

    glColor3f(0xFF,0xFF,0xFF);

    float angle = 1.0f;
    float scale = 0.3f;
    int steps = 360/angle;

    Vector2 normal(1, 1);

   

    for(int i=0 ; i < points.size(); i++){

        glBegin(GL_LINE_LOOP);

        for(int j=0; j<steps; j++){
        
            Vector2 end = normal.Rotate(angle/180.0f * M_PI * j);
            Vector2 direction = (points[i]- end).Normalize();
       
            Vector2 scaled = direction * scale;


            glVertex2f(points[i].x + scaled.x, points[i].y + scaled.y);
        }

        glEnd();
    }
    
    
    

}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    zoomLevel += yoffset * scrollSpeed;

    if (zoomLevel < 0.1f) {
        zoomLevel = 0.1f;
    }
}


static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos){
    
    double normalizedX = (2.0 * xpos / width) - 1.0;
    double normalizedY = 1.0 - (2.0 * ypos / height);

    double adjustedX = normalizedX / zoomLevel;
    double adjustedY = normalizedY / zoomLevel;

    mouseX = adjustedX;
    mouseY = adjustedY;

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