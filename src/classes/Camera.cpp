#include "Camera.h"

Camera::Camera(const GLFWwindow *_window, const float & _width, const float& _height){
    this->window = (GLFWwindow*)_window;
    this->worldBound = Rect(-1.0f,-1.0f,_width, _height);
    this->position = Vector2(0.0f, 0.0f);
    this->zoom = 300.0f;
}

void Camera::Move(const float& _x, const float& _y){
    this->position.x+=_x;
    this->position.y+=_y;
    ClampToWorldBound();
}

void Camera::Move(const Vector2& offset){
    this->position = this->position + offset;
    ClampToWorldBound();
}

void Camera::SetWorldBounds(const float& _width, const float _height){
    this->worldBound.width=_width;
    this->worldBound.height=_height;
}

void Camera::SetPosition(const float& _x, const float& _y){
    this->position.x = _x;
    this->position.y = _y;
    ClampToWorldBound();
}
    
void Camera::SetPosition(const Vector2& offset){
    this->position = offset;
    ClampToWorldBound();
}

Vector2 Camera::GetPosition(){
    return this->position;
}

void Camera::SetZoom(const float& _zoomFactor){
    this->zoom=_zoomFactor;
}

void Camera::AdjustZoom(const float& _zoomFactor){
    this->zoom*=_zoomFactor;
}

void Camera::ClampToWorldBound(){

    float xPos = position.x;
    float yPos = position.y;

    xPos = fmax(0, fmin(xPos,  worldBound.width) );
    yPos = fmax(0, fmin(yPos,  worldBound.height) );

    position.x=xPos;
    position.y=yPos;

}

void Camera::updateProjectionMatrix(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(position.x - worldBound.width / (2.0 * zoom), position.x + worldBound.width / (2.0 * zoom), position.y - worldBound.height / (2.0 * zoom), position.y + worldBound.height / (2.0 * zoom), -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}