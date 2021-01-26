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
    return Search(root, val);
}

template <class T> 
bool BST<T>::Search(unique_ptr<Node<T>>& root, T val)
{
    if (root == nullptr) return false;

    if (root->getVal() < val)
    {
        return Search(root->right, val);
    }
    else if (root->getVal() > val)
    {
        return Search(root->left, val);
    }

    return true; // Found the node.
}

template <class T> 
bool BST<T>::Remove(T val)
{
    root = Remove(root, val);
    return root != nullptr;  
}

template <class T> 
unique_ptr<Node<T>> BST<T>::Remove(unique_ptr<Node<T>>& root, T val)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->getVal() < val) 
    {
        root->right = Remove(root->right, val);
    }
    else if (root->getVal() > val)
    {
        root->left = Remove(root->left, val); 
    }
    else 
    {
        // Found the node, now have to remove it.
        if (root->right == nullptr)
        {
            return move(root->left); 
        }
        if (root->left == nullptr)
        {
            return move(root->right);
        }

        // replace with the right sub trees left most node
        Node<T>* node = root->right.get(); 
        while (node && node->left)
        {
            node = node->left.get();
        }

        root->setVal(node->getVal());

        root->right = Remove(root->right, node->getVal());
    }

    return move(root); 
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

// int main(void)
// {
//     BST<int> bst; 
//     bst.Insert(2);
//     bst.Insert(1);
//     bst.Insert(3);
//     bst.Insert(4);

//     bst.ShowInorder();
    

//     return 0;
// }