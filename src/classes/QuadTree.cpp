#include "QuadTree.h"
#include "GL/gl.h"

QuadTree::QuadTree(const float& _width, const float& _height){

    root = new QuadNode(-1.0f, -1.0f, _width, _height);

}

void QuadTree::InsertObject(const Vector2& _object){

    InsertObject(root, _object);

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
        node->points[node->size++] = _object;
    }
}

void QuadTree::Draw(){
    DrawQuadTreeBoundaries(root);
    glBegin(GL_POINTS);
        Visit(root);
    glEnd();
}

void QuadTree::Visit(const QuadNode* node){
    if(node==NULL)
        return;

    for(auto const &element : node->points){
        glVertex2f(element.x, element.y);
    }

    Visit(node->topLeft);
    Visit(node->topRight);
    Visit(node->bottomLeft);
    Visit(node->bottomLeft);
}

void QuadTree::DrawQuadTreeBoundaries(const QuadNode* node) {

    if(node==NULL)
        return;

    //Draw current node boundary rectangle
    glBegin(GL_LINE_LOOP);
        glVertex2f(node->rect.x, node->rect.y);
        glVertex2f(node->rect.x + node->rect.width, node->rect.y);
        glVertex2f(node->rect.x + node->rect.width, node->rect.y + node->rect.height);
        glVertex2f(node->rect.x, node->rect.y + node->rect.height);
    glEnd();

    //Draw all childs of current node
    DrawQuadTreeBoundaries(node->topLeft);
    DrawQuadTreeBoundaries(node->topRight);
    DrawQuadTreeBoundaries(node->bottomLeft);
    DrawQuadTreeBoundaries(node->bottomRight);
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