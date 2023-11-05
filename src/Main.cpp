
#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #include <GL/glew.h>
    #include <GL/gl.h>
    #include <GLFW/glfw3.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

int width=640, height=480;

void WindowResizeCallback(GLFWwindow *window, int w, int h);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

GLuint CreateTexture(int width, int height, unsigned char* data);

int main(int argc, char *argv[]){

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
    glfwSwapInterval(1);

    glOrtho(0, width, 0, height, -1.0f, 1.0f);

    const GLubyte *vendor = glGetString(GL_VENDOR);
    const GLubyte *renderer = glGetString(GL_RENDERER);

    printf("Vendor : %s\n", vendor);
    printf("Device : %s\n", renderer);
    
    glfwSetWindowSizeCallback(window, WindowResizeCallback);
    glfwSetKeyCallback(window, KeyCallback);

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    while(!glfwWindowShouldClose(window)){

        double currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){ 
            
            printf("%f ms/frame\n", 1000.0/double(nbFrames));
            nbFrames = 0;
            lastTime += 1.0;
        }

        glClear(GL_COLOR_BUFFER_BIT);


        glfwSwapBuffers(window);
        glfwPollEvents();


        GLenum error =glGetError();
        if(error!=GL_NO_ERROR)
            printf("Error : %d\n", error);

    }


    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void WindowResizeCallback(GLFWwindow *window, int w, int h){
    glViewport(0, 0, w, h); //Change viewport size
}


void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        
        if (key == GLFW_KEY_ESCAPE){
            glfwSetWindowShouldClose(window, true);
        }

    }
}

GLuint CreateTexture(int width, int height, unsigned char* data) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}