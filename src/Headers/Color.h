#ifndef COLOR_H
#define COLOR_H

struct Color{
    float R;
    float G;
    float B;

    Color(){
        this->R=1.0f;
        this->G=1.0f;
        this->B=1.0f;
    }

    Color(const float& R, const float&G, const float &B){
        this->R=R;
        this->G=G;
        this->B=B;
    }
};

#endif
