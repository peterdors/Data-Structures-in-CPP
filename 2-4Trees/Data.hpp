#ifndef DATA_HPP
#define DATA_HPP

template <class T> 
struct Data
{
    T val; 
    Data(const T& val)
    {
        this->val = val;
    }
};

#endif