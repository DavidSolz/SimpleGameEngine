#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

struct Ray
{
   
    Vector3 origin;
    Vector3 direction;

    Ray(){}

    Ray(const Vector3& _origin, const Vector3& _direction){
        this->origin=_origin;
        this->direction=_direction;
    }

};


#endif