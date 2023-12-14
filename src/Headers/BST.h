#ifndef BSP_H
#define BSP_H


template<typename T>
struct Node{
    T value;
    Node *left, *right;

    Node(const T& _value){
        this->value = &value;
    }
};

template<typename T>
class BST {

    void AddElement(const T& _value);
    T* FindElement(const T& _value) const;
    void DeleteElement(const T& _value);
    

    ~BST();

private:

    Node<T> *root;

};


#endif