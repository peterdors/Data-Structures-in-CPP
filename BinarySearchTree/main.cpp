#include <iostream>
#include "bst.cpp"
#include <memory>
using namespace std;

int main(void)
{
    BST<int> bst; 
    bst.Insert(2);
    bst.Insert(1);
    bst.Insert(3);
    bst.Insert(4);

    cout << "Searching for 4: " << bst.Search(4) << endl;
    cout << "Searching for 1: " << bst.Search(1) << endl;
    cout << "Searching for 5: " << bst.Search(5) << endl;


    cout << "Removing 4: " << bst.Remove(4) << endl;
    cout << "Removing 1: " << bst.Remove(1) << endl;
    cout << "Removing 5: " << bst.Remove(5) << endl;

    // cout << "Searching for 4: " << bst.Search(4) << endl;
    // cout << "Searching for 1: " << bst.Search(1) << endl;
    // cout << "Searching for 5: " << bst.Search(5) << endl;

    cout << "Showing inorder: ";
    bst.ShowInorder();

    return 0;
}