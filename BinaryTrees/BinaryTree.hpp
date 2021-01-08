#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "Node.hpp"
#include <vector>
#include <string>
using namespace std;

template <class T>
class BinaryTree
{
private:
    /* data */
    Node<T>* root; 

    void ForestFire(Node<T>* root)
    {
        if (root == nullptr) 
        {
            return; 
        }

        ForestFire(root->left);
        ForestFire(root->right);
        delete root;
    }

    Node<T>** Find(T val);
    Node<T>* Remove(Node<T>* node, T val);
    Node<T>* Removee(Node<T>* node);
    Node<T>* GrabLeafNode(Node<T>* node);


public:
    BinaryTree();
    BinaryTree(vector<T>& vals);

    ~BinaryTree()
    {
        ForestFire(root); 
    }

    void Insert(T val);
    bool Search(T val); 
    bool Remove(T val);
    string ToString();
};

#endif
