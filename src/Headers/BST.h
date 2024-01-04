#ifndef BST_H
#define BST_H

#include <stdint.h>
#include <vector>

template<typename T>
struct Node{
    T value;
    Node *left, *right;

    Node(const T& _value){
        this->value = value;
        this->left = NULL;
        this->right = NULL;
    }
};

template<typename T>
class BST {

public:

    BST(){
        size = 0;
        root = NULL;
    }

    void AddElement(const T& _value){

    size++;

    if (!root) {
        root = new Node<T>(_value);
        return;
    }

    Node<T>* current = root;
    
    while (true) {

        if(current->value == _value){
            size--;
            break;

        }else if (_value < current->value) {

            if (!current->left) {
                current->left = new Node<T>(_value);
                break;
            }

            current = current->left;
        } else {

            if (!current->right) {
                current->right = new Node<T>(_value);
                break;
            }

            current = current->right;
        }
    }

}

    T* FindElement(const T& _value) const{

    Node<T> *current = root;

    // Traverse tree and determine if value is defined within any node
    while(current){

        if(current->value == _value){
            return &current->value;
        }else if(current->value < _value){
            current = current->right;
        }else{
            current = current->left;
        }

    }
    
    return nullptr;
}

    void DeleteElement(const T& _value){

        // Break if tree does not contain any element
        if(!root)
            return;
        
        Node<T> *parent = NULL;
        Node<T> *current = root;

        // Traverse tree and determine if value is defined within any node
        while(current){

            if(current->value == _value){
                break;
            }else if(current->value < _value){
                parent = current;
                current = current->right;
            }else{
                parent = current;
                current = current->left;
            }
        
        }

        // Break if tree does not contain specified value
        if(!current)
            return;

        if (!current->left && !current->right) {
            // Case 1: Node has no children
            if (parent) {
                if (parent->left == current)
                    parent->left = NULL;
                else
                    parent->right = NULL;
            } else {
                // Deleting the root
                root = NULL;
            }

            delete current;

        } else if (current->left && !current->right) {
            // Case 2: Node has only left child
            Node<T>* temp = current->left;
            delete current;

            if (parent)
                parent->left = temp;
            else
                root = temp;

        } else if (!current->left && current->right) {
            // Case 3: Node has only right child
            Node<T>* temp = current->right;
            delete current;

            if (parent)
                parent->right = temp;
            else
                root = temp;

        } else {
            // Case 4: Node has both left and right children
            Node<T>* successorParent = current;
            Node<T>* successor = current->right;

            // Find the leftmost node in the right subtree
            while (successor->left) {
                successorParent = successor;
                successor = successor->left;
            }

            // Copy the value of the successor
            current->value = successor->value;

            // Delete the successor (it will be either a leaf or have a right child)
            if (successorParent->left == successor)
                successorParent->left = successor->right;
            else
                successorParent->right = successor->right;

            delete successor;
        }

        size--;
    }

    std::vector<T> GetAllElements(){
        std::vector<T> elements;
        elements.reserve(size);

        InorderTraverse(root, elements);

        return elements;
    }

    bool Empty(){
        return size==0;
    }

    T* Top(){
        return &root->value;
    }

    ~BST(){
        DeleteTree(root);
    }

private:

    Node<T> * FindMinimalNode(const Node<T> *current){

        if(!current->left)
            return (Node<T>*)current;

        return FindMinimalNode(current->left);
    }

    Node<T> * FindMaximalNode(const Node<T> *current){

        if(!current->right)
            return (Node<T>*)current;

        return FindMaximalNode(current->right);
    }

    void DeleteTree(Node<T> *current){
        if(!current)
            return;

        DeleteTree(current->left);
        DeleteTree(current->right);

        delete current;

    }

    void InorderTraverse(const Node<T> *current, std::vector<T> & _vector){
        if(!current)
            return ;

        InorderTraverse(current->left, _vector);
        _vector.emplace_back(current->value);
        InorderTraverse(current->right, _vector);

    }

    uint32_t size;
    Node<T> *root;

};


#endif