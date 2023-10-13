#ifndef VECTORS_H
#define VECTORS_H

#include <cmath>

#pragma once

struct Vector2{
    float x;
    float y;

    Vector2(){}

    Vector2(const float &_x, const float &_y) : x(_x), y(_y){}

    Vector2 operator*(const float &scalar){
        return Vector2(x*scalar, y*scalar);
    }

    Vector2 operator+(const Vector2 &vector){
        return Vector2(x+vector.x, y+vector.y);
    }

    Vector2 operator-(const Vector2 &vector){
        return Vector2(x-vector.x, y-vector.y);
    }

    bool operator==(const Vector2 &vector){
        return x==vector.x && y==vector.y;
    }

    bool operator!=(const Vector2 &vector){
        return x!=vector.x || y!=vector.y;
    }

    float Dot(const Vector2 &vector){
        return x*vector.x + y*vector.y;
    }

    float Dot(const float &vectorALength, const float &vectorBLength, const float &angleBetweenVectors){
        return vectorALength*vectorBLength*cos(angleBetweenVectors);
    }

    virtual float Magnitude(){
        return sqrt(x*x+y*y);
    }

    virtual float Distance(const Vector2 &vector){
        float deltaX = vector.x-x;
        float deltaY = vector.y-y;
        return sqrt(deltaX*deltaX + deltaY*deltaY);
    }

    Vector2 Normalize(){
        float magnitude = Magnitude();
        return Vector2(x/magnitude, y/magnitude);
    }

    Vector2 Rotate(const float &angle){

        float nX = x*cos(angle) - y*sin(angle);
        float nY = x*sin(angle) + y*cos(angle);

        return Vector2(nX, nY);

    }

};

struct Vector3 : public Vector2{

    float z;

    Vector3(){}

    Vector3(const float &_x, const float &_y, const float &_z) : Vector2(_x, _y), z(_z){}

    Vector3 operator*(const float &scalar){
        return Vector3(x*scalar, y*scalar, z*scalar);
    }

    Vector3 operator*(const Vector3 &vector){

        float nX = y*vector.z - vector.y*z;
        float nY = x*vector.z - vector.x*z;
        float nZ = x*vector.y - vector.x*y;

        return Vector3(nX, nY, nZ);
    }

    Vector3 operator+(const Vector3 &vector){
        return Vector3(x+vector.x, y+vector.y, z+vector.z);
    }

    Vector3 operator-(const Vector3 &vector){
        return Vector3(x-vector.x, y-vector.y, z-vector.z);
    }

    float Dot(const Vector3 &vector){
        return x*vector.x + y*vector.y + z*vector.z;
    }

    float Distance(const Vector3 &vector){
        float deltaX = vector.x-x;
        float deltaY = vector.y-y;
        float deltaZ = vector.z-z;
        return sqrt(deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ);
    }

    float Magnitude(){
        return sqrt(x*x+y*y+z*z);
    }

    Vector3 Normalize(){
        float magnitude = Magnitude();
        return Vector3(x/magnitude, y/magnitude, z/magnitude);
    }

};


#endif
