#ifndef NODE_HPP
#define NODE_HPP

#include "Data.hpp"
#include <iostream>

template <class T> 
struct Node 
{
    const static int ORDER = 4; 

    int numItems; 
    Data<T>* vals[ORDER-1]; // consider wrapping in struct

    Node<T>* parent;
    Node<T>* childs[ORDER];

    Node<T>() 
    {
        numItems = 0; 

        for (int i = 0; i < ORDER; i++)
        {
            childs[i] = nullptr;
            if (i < ORDER - 1)
            {
                vals[i] = nullptr;
            }
        }
    }
    
    bool isFull()
    {
        return numItems >= ORDER - 1; 
    }

    bool isLeaf()
    {
        // for (auto child : childs)
        // {
        //     if (child != nullptr)
        //     {
        //         return false;
        //     }
        // }

        // return true;



        // Alternative...
        return childs[0] == nullptr; 
        
    }

    bool isSingleNodeInTree()
    {
        return parent == nullptr && childs[0] == nullptr && numItems <= 1;
    }

    Node<T>* getParent()
    {
        return this->parent;
    }

    int insertItem(Data<T>* newData)
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
                    // for (int j = 0; j < numItems; j++)
                    // {
                    //     std::cout << vals[j]->val << std::endl;
                    // }

                    vals[i+1] = vals[i];
                }
                else 
                {
                    vals[i+1] = newData;
                    return i + 1;
                }
            }
            
        }

        vals[0] = newData;
        return 0;
    }

    Data<T>* removeItem()
    {
        Data<T>* data = vals[numItems - 1]; 
        vals[numItems - 1] = nullptr;
        numItems--;

        return data; 
    }

    Node<T>* disconnectChild(int childNum)
    {
        Node<T>* node = childs[childNum];
        childs[childNum] = nullptr;

        return node;
    }

    void connectChild(int childNum, Node<T>* child)
    {
        childs[childNum] = child;
        if (child != nullptr)
        {
            child->parent = this;
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

        delete vals[numItems-1]; 
        vals[numItems-1] = nullptr;
        numItems--;
    }

    void insertAtFront(Data<T>* d)
    {
        numItems++; 
        for (int j = numItems - 1; j > 0; j--)
        {
            vals[j] = vals[j-1];
            connectChild(j + 1, disconnectChild(j));
        }

        connectChild(1, disconnectChild(0));
        vals[0] = d; 
        connectChild(0, nullptr);
    }
};

#endif 