#ifndef DATA_HPP
#define DATA_HPP

template <class T> 
struct Data
{
    T val;
    Data(T val)
    {
        this->val = val; 
    }
};

#endif