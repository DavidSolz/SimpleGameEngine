#ifndef VECTOR3_H
#define VECTOR3_H

#include "Vector2.h"

struct Vector3 : public Vector2{

    float z;

    Vector3(){
        this->x=0;
        this->y=0;
        this->z=0;
    }

    Vector3(const float &_x, const float &_y, const float &_z){
        this->x=_x;
        this->y=_y;
        this->z=_z;
    }

    Vector3(const float &_x, const float &_y){
        this->x=_x;
        this->y=_y;
        this->z=0;
    }

    float Magnitude(){
        return sqrt(x*x + y*y + z*z);
    }

    float sqrMagnitude(){
        return x*x+y*y+z*z;
    }

    Vector3 Normalize(){
        float magnitude = Magnitude();
        return Vector3(x/magnitude, y/magnitude, z/magnitude);
    }

    Vector3 Rotate(const float &angle){

        //TODO : rotate by Z-axis

        float nX = x*cos(angle) - y*sin(angle);
        float nY = x*sin(angle) + y*cos(angle);
        float nZ = z;

        return Vector3(nX, nY, nZ);
    }

//Static member functions

    static float Dot(const Vector3 &vectorA, const Vector3 &vectorB){
        return vectorA.x*vectorB.x + vectorA.y*vectorB.y + vectorA.z*vectorB.z;
    }

    static float Distance(const Vector3 &vectorA, const Vector3 &vectorB){
        float deltaX = vectorA.x-vectorB.x;
        float deltaY = vectorA.y-vectorB.y;
        float deltaZ = vectorA.z-vectorB.z;

        return sqrt(deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ);
    }

    static Vector3 Lerp(const Vector3& vectorA, const Vector3& vectorB, const float &t){
        
        float step = std::fmin(t, 1.0f);
        step = std::fmax(step, 0.0f);

        float lerpX = vectorA.x + (vectorB.x-vectorA.x)*step;
        float lerpY = vectorA.y + (vectorB.y-vectorA.y)*step;
        float lerpZ = vectorA.z + (vectorB.z-vectorA.z)*step;

        return Vector3(lerpX, lerpY, lerpZ);
    }

    static Vector3 Max(const Vector3 &vectorA, const Vector3 &vectorB){

        float xMax = std::max(vectorA.x, vectorB.x);
        float yMax = std::max(vectorA.y, vectorB.y);
        float zMax = std::max(vectorA.z, vectorB.z);

        return Vector3(xMax, yMax, zMax);
    }

    static Vector3 Min(const Vector3 &vectorA, const Vector3 &vectorB){

        float xMin = std::min(vectorA.x, vectorB.x);
        float yMin = std::min(vectorA.y, vectorB.y);
        float zMin = std::min(vectorA.z, vectorB.z);

        return Vector3(xMin, yMin, zMin);
    }

    static Vector3 MoveTowards(const Vector3 &current, const Vector3 &target, const float &step){

        Vector3 normalized = ((Vector3)target-(Vector3)current).Normalize();
        Vector3 forceVector = normalized*step;

        return (Vector3)current + forceVector;
    }

    static Vector3 Reflect(const Vector3 & vector, const Vector3 &planeNormal){

        Vector3 projection = (Vector3)planeNormal * (Dot(vector, planeNormal)/Dot(planeNormal, planeNormal));
        Vector3 reflection = (Vector3)vector - projection * 2.0f;

        return reflection;
    }

    static Vector3 Scale(const Vector3 & vectorA, const Vector3 &vectorB){

        float scaleX = std::abs(vectorA.x/vectorB.x);
        float scaleY = std::abs(vectorA.y/vectorB.y);
        float scaleZ = std::abs(vectorA.z/vectorB.z);

        return Vector3(scaleX, scaleY, scaleZ);
    }

//Operators

    Vector3 operator+(const Vector3 &vector){
        return Vector3(x+vector.x, y+vector.y, z+vector.z);
    }

    Vector3 operator-(const Vector3 &vector){
        return Vector3(x-vector.x, y-vector.y, z-vector.z);
    }

    Vector3 operator*(const float &scalar){
        return Vector3(x*scalar, y*scalar, z*scalar);
    }

    Vector3 operator/(const float &scalar){
        float factor = 1/scalar;
        return Vector3(x*factor, y*factor, z*factor);
    }

    Vector3 operator*(const Vector3 &vector){

        float nX = y*vector.z - vector.y*z;
        float nY = x*vector.z - vector.x*z;
        float nZ = x*vector.y - vector.x*y;

        return Vector3(nX, nY, nZ);
    }

    bool operator==(const Vector3 &vector){
        return x==vector.x && y==vector.y && z==vector.z;
    }

    bool operator!=(const Vector3 &vector){
        return x!=vector.x || y!=vector.y || z!=vector.z;
    }

};


#endif
