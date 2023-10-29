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

    bool isInBound(const Vector2& _object) {
        return (_object.x >= x && _object.x < x + width &&
         _object.y >= y && _object.y < y + height);
    }

    bool isInBound(const Rect& _rect) {
        return (_rect.x >= x && _rect.x + _rect.width < x + width &&
         _rect.y >= y && _rect.y + _rect.height < y + height);
    }

    bool isIntersecting(const Rect& _other) {
        return std::fmax(x, _other.x) < std::fmin(x+width, _other.x+_other.width) &&
                std::fmax(y, _other.y) < std::fmin(y+height, _other.y + _other.height);

    }


};

#endif
