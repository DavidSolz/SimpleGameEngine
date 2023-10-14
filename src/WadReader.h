#ifndef WADREADER_H
#define WADREADER_H

#include "Vector2.h"
#include "fstream"
#include "string"

enum Indices{
    THINGS = 1,
    LINEDEFS,
    SIDEDEFS,
    VERTEXES,
    SEGS,
    SSECTORS,
    NODES,
    SECTORS,
    REJECT,
    BLOCKMAP
};

class WadReader{

unsigned int lumpNumber;
unsigned int infoTableOffset;
unsigned char buffer[128];
std::ifstream input;


public:

    WadReader(const std::string fileName){

        input.open(fileName, std::ios::in);
        if(!input){
            printf("Error during opening the file\n");
            return ;
        }
    }


    void ReadHeader(){

        input.read((char*)buffer, 4);

        lumpNumber|= buffer[7];
        lumpNumber<<= 8;
        lumpNumber|= buffer[6];
        lumpNumber<<= 8;
        lumpNumber|= buffer[5];
        lumpNumber<<= 8;
        lumpNumber|= buffer[4];
        
        printf("Lumps : %d\n", lumpNumber);

    }

    void ReadChunks(){
        
        if(!input)
            return;

        ReadHeader();

        input.close();
    }



};

#endif