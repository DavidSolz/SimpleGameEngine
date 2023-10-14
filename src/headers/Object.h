#ifndef OBJECT_H
#define OBJECT_H

#include <string>

struct Object{

    Object(){
        this->GUID=idCounter++;
    }

    unsigned int GetGUID(){
        return GUID;
    }

    virtual std::string ToString(){
        return "Object " + std::to_string(GUID);
    }


//Static member functions

//TODO

private:

    unsigned int GUID;


//Static properties

    static unsigned int idCounter;



};

#endif