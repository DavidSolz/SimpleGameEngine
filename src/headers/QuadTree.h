#ifndef QUADTREE_H
#define QUADTREE_H

#include "Rect.h"

#define CAPACITY 8

struct QuadTree
{

    QuadTree(const float& _width, const float & _height);
 
    void InsertObject(const Vector2& _object);

    void Clean();

    void Draw();

    ~QuadTree();

    private:

    struct QuadNode{
        int size;
        Rect rect;
        Vector2 points[CAPACITY];

        QuadNode *topLeft;
        QuadNode *topRight;
        QuadNode *bottomLeft;
        QuadNode *bottomRight;
        
        QuadNode(const float& _x, const float& _y, const float& _width, const float& _height){
            this->size=0;
            this->rect = Rect(_x, _y, _width, _height);
            topLeft=topRight=bottomLeft=bottomRight=NULL;
        }

        bool isInBound(const Vector2& _object){
            return rect.isInBound(_object);
        }

    };

    QuadNode *root;

    void Visit(const QuadNode *node);
    void DeleteQuadTree(QuadNode *node);
    void DrawQuadTreeBoundaries(const QuadNode *node);
    void InsertObject(QuadNode *node, const Vector2& _object);
    
};

#endif