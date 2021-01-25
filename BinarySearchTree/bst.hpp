#ifndef BST_HPP
#define BST_HPP
#include <memory>
#include "node.hpp"
using namespace std;

template <class T>
class BST
{
private:
    unique_ptr<Node<T>> root; 
    unique_ptr<Node<T>> Insert(unique_ptr<Node<T>>& root, T val);
    void inorder(unique_ptr<Node<T>>& root);

public:
    BST();
    ~BST();

    void Insert(T val); 
    bool Search(T val);
    void Remove(T val);
    void ShowInorder();
};


#endif