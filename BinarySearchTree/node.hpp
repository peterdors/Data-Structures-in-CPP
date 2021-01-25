#ifndef NODE_HPP
#define NODE_HPP
#include "data.hpp"
#include <memory> 
using namespace std;

template <class T> 
struct Node 
{
    unique_ptr<Data<T>> data; 
    unique_ptr<Node<T>> left, right;

    Node<T>() {}

    Node<T>(T val) : Node<T>()
    {
        data = unique_ptr<Data<T>>(new Data<T>(val));
    }

    T getVal()
    {
        return this->data->val;
    }

    void setVal(T val)
    {
        if (this->data)
        {
            this->data->val = val;
        }
        else
        {
            this->data = unique_ptr<Data<T>>(new Data<T>(val));
        }
    }

};

#endif