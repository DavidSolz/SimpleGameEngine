#include "QuadTree.h"

QuadTree::QuadTree(const float& _width, const float& _height){

    root = new QuadNode(-1.0f, -1.0f, _width, _height);

}

void QuadTree::InsertObject(const Vector2& _object){

    InsertObject(root, _object);

}

void QuadTree::Query(std::list<Vector2> &points, const Rect &worldBound){

    Query(root, points, worldBound);

}

void QuadTree::Query(const QuadNode *node, std::list<Vector2> &points, const Rect &worldBound){
    if(node==NULL || !((Rect)worldBound).isIntersecting(node->rect))
        return;

    if(((Rect)worldBound).isInBound(node->rect)){
        for(int i =0; i< node->size; i++){
            points.push_back(node->points[i]);
        }
        return;
    }

    Query(node->topLeft, points, worldBound);
    Query(node->topRight, points, worldBound);
    Query(node->bottomLeft, points, worldBound);
    Query(node->bottomRight, points, worldBound);

}

void QuadTree::GetAllObjects(std::list<Vector2> &points){
    AcquireObjects(points, root);
}

void QuadTree::AcquireObjects(std::list<Vector2> &points, const QuadNode * node){
    if(node==NULL)
        return;

    for(int i =0; i< node->size; i++){
        points.push_back(node->points[i]);
    }

    AcquireObjects(points, node->topLeft);
    AcquireObjects(points, node->topRight);
    AcquireObjects(points, node->bottomLeft);
    AcquireObjects(points, node->bottomRight);
}

void QuadTree::InsertObject(QuadNode *node, const Vector2& _object){
    if (node == NULL) {
        return;
    }

    if (node->size >= CAPACITY) {
        // Subdivide the node if it's reached capacity
        if (node->topLeft == NULL) {
            float verticalMiddle = node->rect.x + node->rect.width / 2.0f;
            float horizontalMiddle = node->rect.y + node->rect.height / 2.0f;

            // Create child nodes for each quadrant
            node->topLeft = new QuadNode(node->rect.x, horizontalMiddle, verticalMiddle - node->rect.x, node->rect.y + node->rect.height - horizontalMiddle);
            node->topRight = new QuadNode(verticalMiddle, horizontalMiddle, node->rect.x + node->rect.width - verticalMiddle, node->rect.y + node->rect.height - horizontalMiddle);
            node->bottomLeft = new QuadNode(node->rect.x, node->rect.y, verticalMiddle - node->rect.x, horizontalMiddle - node->rect.y);
            node->bottomRight = new QuadNode(verticalMiddle, node->rect.y, node->rect.x + node->rect.width - verticalMiddle, horizontalMiddle - node->rect.y);
        }

        // Check which child node the object should be inserted into
        if (node->topLeft->isInBound(_object)) {
            InsertObject(node->topLeft, _object);
        } else if (node->topRight->isInBound(_object)) {
            InsertObject(node->topRight, _object);
        } else if (node->bottomLeft->isInBound(_object)) {
            InsertObject(node->bottomLeft, _object);
        } else if (node->bottomRight->isInBound(_object)) {
            InsertObject(node->bottomRight, _object);
        }
    } else {
        // Insert the object into the current node

        //Check if object is already present at that cooridantes
        for(int i =0; i< node->size; i++){
            if(node->points[i]==_object)
                return;
        }

        node->points[node->size++] = _object;
    }
}

void QuadTree::DeleteQuadTree(QuadNode* node) {
    if (node == NULL)
        return;

    DeleteQuadTree(node->bottomLeft);
    DeleteQuadTree(node->bottomRight);
    DeleteQuadTree(node->topLeft);
    DeleteQuadTree(node->topRight);

    delete node;
}

void QuadTree::Clean(){
    DeleteQuadTree(root);
    root = new QuadNode(-1.0f, -1.0f, 2.0f, 2.0f);
}

QuadTree::~QuadTree(){
    DeleteQuadTree(root);
}
