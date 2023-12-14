#include "BST.h"

template<typename T>
void BST<T>::AddElement(const T& _value){

    Node<T>* newNode = new Node<T>(_value);

    if (!root) {
        root = newNode;
        return;
    }

    Node<T>* current = root;
    while (true) {

        if (_value < current->data) {

            if (!current->left) {
                current->left = newNode;
                break;
            }

            current = current->left;
        } else {

            if (!current->right) {
                current->right = newNode;
                break;
            }

            current = current->right;
        }
    }
    
}

template<typename T>
T* BST<T>::FindElement(const T& _value) const{

    Node<T> *current = root;

    while(current != NULL){

        if(current->value == _value){
            return &current->value;
        }else if(current->value < _value){
            current = current->right;
        }else{
            current = current->left;
        }

    }
    
    return NULL;
}

template<typename T>
void BST<T>::DeleteElement(const T& _value){

    Node<T> *parent = NULL;
    Node<T> *current = root;

    while(current){

        parent = current;

        if(current->value == _value){
            break;
        }else if(current->value < _value){
            current = current->right;
        }else{
            current = current->left;
        }

    }

    if(!current)
        return;




}

template<typename T>
BST<T>::~BST(){
    
}
