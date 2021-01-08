#ifndef NODE_H
#define NODE_H

template <typename T> 
struct Node 
{
    T val; 
    Node<T>* left; 
    Node<T>* right;

    Node<T>(T val) 
    {
        this->val = val;
        this->left = nullptr; 
        this->right = nullptr; 
    }

};

#endif