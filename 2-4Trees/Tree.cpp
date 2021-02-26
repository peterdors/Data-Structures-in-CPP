#include "Tree.hpp"
#include <iostream>
// using namespace std; 

int main(void)
{
    Tree<int> t; 

    int vals[] = {61, 51, 16, 20, 55, 76, 85, 93, 65, 71, 81, 90, 101};
    //   
    
    for (int val : vals)
    {
        t.Insert(val); 
    }
    
    t.recDisplay();


    // for (int val : vals)
    // {
    //     cout << "Searching " << val << ": " << t.Search(val) << endl;    
    // }

    
    // cout << "Removing " << 0 << ": " << t.Remove(0) << endl;
    
    // for (int val : vals)
    // {
    //     // cout << "Removing " << 0 << ": " << t.Remove(0) << endl;
    //     cout << "Removing " << val << ": " << t.Remove(val) << endl;
    //     // cout << "Removing " << 0 << ": " << t.Remove(0) << endl;
    // }

    // cout << "Removing " << 0 << ": " << t.Remove(0) << endl;
    
    // t.inorder();
    // t.recDisplay();

    return 0; 
}