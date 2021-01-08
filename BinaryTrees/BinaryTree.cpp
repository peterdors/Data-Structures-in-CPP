#include "BinaryTree.hpp"
#include <queue>
#include <ostream>
#include <sstream>
#include <iostream>

template <class T> 
BinaryTree<T>::BinaryTree() {root = nullptr;}

template <class T> 
BinaryTree<T>::BinaryTree(vector<T>& vals)
{
    // root = vals.front();
    /*

        [1,2,3,4]

                 1
                / \
               2   3
              /
             4
    

        [1,null,2,3,4]

                 1
                / \
             null  2
                  / \
                 3   4
    
    */




}

template <class T>
void BinaryTree<T>::Insert(T val) 
{
    if (root == nullptr)
    {
        root = new Node<T>(val);
        return; 
    }

    queue<Node<T>*> q; 

    q.push(root); 
    while (!q.empty())
    {
        int n = q.size(); 
        for (int i = 0; i < n; i++)
        {
            Node<T>* curr = q.front();
            q.pop();

            if (curr == nullptr)
            {
                continue;
            }
            else if (curr->left == nullptr)
            {
                curr->left = new Node<T>(val);
                cout << "inserted " << val << endl;
                return; 
            }
            else if (curr->right == nullptr)
            {
                curr->right = new Node<T>(val);
                cout << "inserted " << val << endl;
                return; 
            }
            else
            {
                q.push(curr->left); 
                q.push(curr->right); 
            }
        }

    }
}

template <class T>
bool BinaryTree<T>::Search(T val)
{
    return Find(val) != nullptr;
}

template <class T>
Node<T>** BinaryTree<T>::Find(T val)
{
    if (root == nullptr)
    {
        return nullptr; 
    }

    if (root->val == val)
    {
        return &root; 
    }

    queue<Node<T>**> q; 
    q.push(&root); 

    while (!q.empty())
    {
        int n = q.size(); 

        for (int i = 0; i < n; i++)
        {
            Node<T>** curr = q.front(); 
            q.pop();

            if (*curr == nullptr)
            {
                continue;
            }

            if ((*curr)->val == val)
            {
                return curr; 
            }
            else
            {
                q.push(&((*curr)->left));
                q.push(&((*curr)->right));
            }
        }
    }

    return nullptr;
}

template <class T>
bool BinaryTree<T>::Remove(T val)
{
    // Find and remove the node with val from the tree, 
    // then update that node with one of the leaves if 
    // appropriate.  
    Node<T>** sought = Find(val);
    if (sought == nullptr) return false; 

    *sought = Removee(*sought);
    return true;
}

template <class T>
Node<T>* BinaryTree<T>::Removee(Node<T>* node)
{
    if (node->left == nullptr)
    {
        Node<T>* temp = node->right;
        delete node;
        return temp; 
    }
    else if (node->right == nullptr)
    {
        Node<T>* temp = node->left;
        delete node; 
        return temp;
    }
    else
    {
        Node<T>* leaf = GrabLeafNode(node->right);
        node->val = (leaf)->val; 
        node->right = Remove(node->right, leaf->val);
    }

    return node; 
}

template <class T>
Node<T>* BinaryTree<T>::Remove(Node<T>* node, T val)
{
    if (node == nullptr)
    {
        return node; 
    }

    if (node->val == val)
    {
        if (node->left == nullptr)
        {
            Node<T>* temp = node->right;
            delete node;
            return temp; 
        }
        else if (node->right == nullptr)
        {
            Node<T>* temp = node->left;
            delete node; 
            return temp;
        }
        else
        {
            Node<T>* leaf = GrabLeafNode(node->right);
            node->val = leaf->val; 
            node->right = Remove(node->right, leaf->val);
        }
    }

    node->left = Remove(node->left, val);
    node->right = Remove(node->right, val);

    return node;
}

template <class T>
Node<T>* BinaryTree<T>::GrabLeafNode(Node<T>* node)
{
    Node<T>* curr = node; 

    while (curr != nullptr && curr->right != nullptr)
    {
        curr = curr->right; 
    }

    return curr;
}

template <class T> 
string BinaryTree<T>::ToString()
{
    queue<Node<T>*> q; 
    q.push(root); 
    ostringstream ss; 
    ss.str("");

    while (!q.empty())
    {
        ss << "["; 

        int n = q.size(); 
        for (int i = 0; i < n; i++)
        {
            Node<T>* curr = q.front(); 
            q.pop(); 

            if (curr == nullptr)
            {
                ss << "null" << ((i + 1 == n ? "]" : " ")); 
            }
            else
            {
                ss << curr->val << ((i + 1 == n ? "]" : " "));
                q.push(curr->left); 
                q.push(curr->right);
            }
        }
    }
    return ss.str();
}

int main(void)
{
    BinaryTree<int> bt;
    bt.Insert(10); 
    bt.Insert(20); 
    bt.Insert(30);
    bt.Insert(40);

    cout << bt.ToString() << endl;

    cout << "Found val 10 in tree? : " << bt.Search(10) << endl;
    cout << "Found val 20 in tree? : " << bt.Search(20) << endl;
    cout << "Found val 30 in tree? : " << bt.Search(30) << endl;
    cout << "Found val 40 in tree? : " << bt.Search(40) << endl;
    cout << "Found val 40 in tree? : " << bt.Search(40) << endl;
    cout << "Found val 50 in tree? : " << bt.Search(50) << endl;

    bt.Remove(10);
    bt.Remove(20);
    bt.Remove(30);
    bt.Remove(10);
    bt.Remove(40);
    bt.Remove(40);
    // cout << "Remove val 20 in tree? : " <<  bt.Remove(20) << endl;
    // cout << "Remove val 30 in tree? : " << bt.Remove(30) << endl;
    // cout << "Remove val 40 in tree? : " << bt.Remove(40) << endl;
    // cout << "Remove val 40 in tree? : " << bt.Remove(40) << endl;

    cout << bt.ToString() << endl;

    return 0;  
}