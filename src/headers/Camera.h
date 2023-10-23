#ifndef CAMERA_H
#define CAMERA_H

#include "Rect.h"
#include <GLFW/glfw3.h>
#include <cmath>

struct Camera{
    
    float zoom;
    Vector2 position;
    Rect worldBound;
    GLFWwindow *window;

    Camera(){}

    Camera(const GLFWwindow *_window, const float & _width, const float& _height);

    Vector2 GetPosition();

    void SetPosition(const float& _x, const float& _y);

    void SetWorldBounds(const float& _width, const float _height);

    void SetPosition(const Vector2& offset);

    void Move(const float& _x, const float& _y);

    void Move(const Vector2& offset);

    void SetZoom(const float& _zoomFactor);

    void AdjustZoom(const float& _zoomFactor);

    void ClampToWorldBound();

    void updateProjectionMatrix();

};

#endif