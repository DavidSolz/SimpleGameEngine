#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

struct Vector2{

    float x;
    float y;

    Vector2(){
        this->x=0;
        this->y=0;
    }

    Vector2(const float &_x, const float &_y){
        this->x=_x;
        this->y=_y;
    }

    float Magnitude(){
        return sqrt(x*x+y*y);
    }

    float sqrMagnitude(){
        return x*x+y*y;
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

//Static member functions

    static float Dot(const Vector2 &vectorA, const Vector2 &vectorB){
        return vectorA.x*vectorB.x + vectorA.y*vectorB.y;
    }

    static float Dot(const float &vectorALength, const float &vectorBLength, const float &angleBetweenVectors){
        return vectorALength*vectorBLength*cos(angleBetweenVectors);
    }

    static Vector2 Hadamard(const Vector2 &vectorA, const Vector2 &vectorB){
        return Vector2(vectorA.x*vectorB.x, vectorA.y*vectorB.y);
    }

    static Vector2 Lerp(const Vector2& vectorA, const Vector2& vectorB, const float &t){

        float step = std::fmin(t, 1.0f);
        step = std::fmax(step, 0.0f);

        float lerpX = vectorA.x + (vectorB.x-vectorA.x)*step;
        float lerpY = vectorA.y + (vectorB.y-vectorA.y)*step;

        return Vector2(lerpX, lerpY);
    }

    static float Distance(const Vector2 &vectorA, const Vector2 &vectorB){
        float deltaX = vectorA.x-vectorB.x;
        float deltaY = vectorA.y-vectorB.y;
        return sqrt(deltaX*deltaX + deltaY*deltaY);
    }

    static Vector2 Max(const Vector2 &vectorA, const Vector2 &vectorB){

        float xMax = std::fmax(vectorA.x, vectorB.x);
        float yMax = std::fmax(vectorA.y, vectorB.y);

        return Vector2(xMax, yMax);
    }

    static Vector2 Min(const Vector2 &vectorA, const Vector2 &vectorB){

        float xMin = std::fmin(vectorA.x, vectorB.x);
        float yMin = std::fmin(vectorA.y, vectorB.y);

        return Vector2(xMin, yMin);
    }

    static Vector2 MoveTowards(const Vector2 &current, const Vector2 &target, const float &t){

        float step = std::fmin(t, 1.0f);
        step = std::fmax(step, 0.0f);

        Vector2 normalized = ((Vector2)target-(Vector2)current).Normalize();
        Vector2 forceVector = normalized*step;

        return (Vector2)current + forceVector;
    }

    static Vector2 Reflect(const Vector2 & vector, const Vector2 &planeNormal){

        Vector2 projection = (Vector2)planeNormal * (Vector2::Dot(vector, planeNormal)/Vector2::Dot(planeNormal, planeNormal));
        Vector2 reflection = (Vector2)vector - projection * 2.0f;

        return reflection;
    }

    static Vector2 Scale(const Vector2 & vectorA, const Vector2 &vectorB){

        float scaleX = std::abs(vectorA.x/vectorB.x);
        float scaleY = std::abs(vectorA.y/vectorB.y);

        return Vector2(scaleX, scaleY);
    }

//Operators

    Vector2 operator+(const Vector2 &vector){
        return Vector2(x+vector.x, y+vector.y);
    }

    Vector2 operator-(const Vector2 &vector){
        return Vector2(x-vector.x, y-vector.y);
    }

    Vector2 operator*(const float &scalar){
        return Vector2(x*scalar, y*scalar);
    }
    
    float operator*(const Vector2 &vector){
        return x*vector.y - y*vector.x;
    }

    Vector2 operator/(const float &scalar){
        float factor = 1/scalar;
        return Vector2(x*factor, y*factor);
    }

    bool operator==(const Vector2 &vector){
        return x==vector.x && y==vector.y;
    }

    bool operator!=(const Vector2 &vector){
        return x!=vector.x || y!=vector.y;
    }

};

#endif
