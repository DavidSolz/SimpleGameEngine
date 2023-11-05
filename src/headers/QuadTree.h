#ifndef QUADTREE_H
#define QUADTREE_H

#include "Rect.h"
#include <list>

#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #include "GL/gl.h"
#endif


#define CAPACITY 8

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

        bool isInBound(const Rect& _object){
            return rect.isInBound(_object);
        }

    };

class QuadTree{
public:
    QuadTree(const float& _width, const float & _height);
 
    void InsertObject(const Vector2& _object);
    void Clean();
    void Query(std::list<Vector2> &points, const Rect &worldBound);
    void GetAllObjects(std::list<Vector2> &points);

    ~QuadTree();

private:

    QuadNode *root;

    void DeleteQuadTree(QuadNode *node);
    void AcquireObjects(std::list<Vector2> &points, const QuadNode * node);
    void Query(const QuadNode *node, std::list<Vector2> &points, const Rect &worldBound);
    void InsertObject(QuadNode *node, const Vector2& _object);

};

#endif
