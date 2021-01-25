#include "bst.hpp"
#include <iostream>
using namespace std; 

template <class T> 
BST<T>::BST() {}

template <class T> 
BST<T>::~BST() {}

template <class T> 
void BST<T>::Insert(T val)
{
    root = Insert(root, val);
}

template <class T>
unique_ptr<Node<T>> BST<T>::Insert(unique_ptr<Node<T>>& root, T val)
{
    if (root == nullptr)
    {
        root = unique_ptr<Node<T>>(new Node<T>());
        root->data = unique_ptr<Data<T>>(new Data<T>(val));

        return move(root);
    }

    if (root->getVal() > val)
    {
        // move left
        root->left = Insert(root->left, val);
    }

    else if (root->getVal() < val)
    {
        // move right
        root->right = Insert(root->right, val);;
    }

    else 
    {
        ; // already in tree
    }

    return move(root);
}

template <class T> 
bool BST<T>::Search(T val)
{
    return false;
}

template <class T> 
void BST<T>::Remove(T val)
{
    ;
}

template <class T> 
void BST<T>::ShowInorder()
{
    inorder(root); 
    cout << endl;
}

template <class T> 
void BST<T>::inorder(unique_ptr<Node<T>>& root)
{
    if (root == nullptr) return;

    inorder(root->left); 
    cout << root->getVal() << " "; 
    inorder(root->right);
}

int main(void)
{
    BST<int> bst; 
    bst.Insert(2);
    bst.Insert(1);
    bst.Insert(3);
    bst.Insert(4);

    bst.ShowInorder();
    

    return 0;
}