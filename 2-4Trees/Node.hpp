#ifndef NODE_HPP
#define NODE_HPP

#include "Data.hpp"
#include <iostream>
#include <memory>
using namespace std;

template <class T> 
struct Node 
{
    const static int ORDER = 4; 

    int numItems; 
    // Unique pointer because this data is only contained and managed within 
    // this instance of a node(?)
    // Data<T>* vals[ORDER-1]; // consider wrapping in struct
    unique_ptr<Data<T>> vals[ORDER-1];
    
    // Parent would be a shared pointer because multiple nodes can have the same parent. 
    shared_ptr<Node<T>> parent;
    // Childs would be unique pointers because a parent is the owner of the childs. 
    // Note: trying to work with shared pointers on the parent might require us 
    // to use the shared pointer object for childs. 
    shared_ptr<Node<T>> childs[ORDER];

    Node<T>() 
    {
        numItems = 0; 

        for (int i = 0; i < ORDER; i++)
        {
            childs[i] = nullptr;
            if (i < ORDER - 1)
            {
                vals[i] = move(nullptr);
            }
        }
    }
    
    bool isFull()
    {
        return numItems >= ORDER - 1; 
    }

    bool isLeaf()
    {
        // Alternative...
        return childs[0] == nullptr; 
    }

    bool isSingleNodeInTree()
    {
        return parent == nullptr && childs[0] == nullptr && numItems <= 1;
    }

    shared_ptr<Node<T>> getParent()
    {
        return this->parent;
    }

    int insertItem(unique_ptr<Data<T>> newData)
    {
        numItems++;

        for (int i = numItems - 1; i >= 0; i--)
        {
            if (vals[i] == nullptr)
            {
                continue;
            }
            else
            {
                if (newData->val < vals[i]->val)
                {
                    vals[i+1] = move(vals[i]);
                }
                else 
                {
                    vals[i+1] = move(newData);
                    return i + 1;
                }
            }
        }

        vals[0] = move(newData);
        return 0;
    }

    unique_ptr<Data<T>> removeItem()
    {
        // unique_ptr<Data<T>> data = move(vals[numItems - 1]); 
        // vals[numItems - 1] = move(nullptr);
        numItems--;

        // return move(data);
        return move(vals[numItems]); 
    }

    shared_ptr<Node<T>> disconnectChild(int childNum)
    {
        shared_ptr<Node<T>> node (childs[childNum]);
        childs[childNum] = nullptr;

        return node;
    }

    void connectChild(int childNum, shared_ptr<Node<T>> child)
    {
        childs[childNum] = child;
        if (child != nullptr)
        {
            shared_ptr<Node<T>> temp (this);
            child->parent = temp;
        } 
    }

    Node<T>* getSibling(T val)
    {
        Node<T>* child = nullptr;
        Node<T>* p = this->getParent();

        if (numItems != 0)
        {
            for (int i = 0; i <= p->numItems; i++)
            {
                if (p->childs[i]->vals[0]->val < val)
                {
                    child = p->childs[i];
                }
            }
        }
        else if (numItems == 0)
        {
            for (int i = 0; i <= p->numItems; i++)
            {
                if (p->childs[i]->vals[0] == nullptr)
                {
                    if (i != 0)
                    {
                        child = p->childs[i-1];
                    }
                }
            }
        }

        return child; 
    }

    void deleteNodeValue(T val)
    {
        bool flag = false;

        for (int i = 0; i < numItems; i++)
        {
            if (val == vals[i]->val)
            {
                flag = true;
            }
            if (flag && i + 1 < numItems)
            {
                vals[i]->val = vals[i+1]->val;
            }
        }

        // delete vals[numItems-1]; 
        vals[numItems-1] = move(nullptr);
        numItems--;
    }

    void insertAtFront(unique_ptr<Data<T>> d)
    {
        numItems++; 
        for (int j = numItems - 1; j > 0; j--)
        {
            vals[j] = move(vals[j-1]);
            connectChild(j + 1, disconnectChild(j));
        }

        connectChild(1, disconnectChild(0));
        vals[0] = move(d); 
        connectChild(0, nullptr);
    }
};

#endif 