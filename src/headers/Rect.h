#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Vector2.h"

struct Rect
{
    float x, y, width, height;

    Rect(){
        x=1.0f;
        y=1.0f;
        width=1.0f;
        height=1.0f;
    }

    Rect(const float& _x, const float& _y, const float& _width, const float& _height){
        this->x=_x;
        this->y=_y;
        this->width=_width;
        this->height=_height;
    }

    bool isInBound(const Vector2& _object);
    bool isInBound(const Rect& _rect);
    bool isIntersecting(const Rect& _other);

};

#endif