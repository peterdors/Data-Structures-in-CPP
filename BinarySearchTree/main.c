#include <iostream>
#include "bst.hpp"
#include <memory>
using namespace std;

int main(void)
{
    BST<int> bst; 
    bst.Insert(2);
    bst.Insert(1);
    bst.Insert(3);
    bst.Insert(4);

    return 0;
}