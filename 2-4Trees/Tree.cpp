#include "Tree.hpp"
#include <iostream>
using namespace std; 

int main(void)
{
    Tree<int> t; 

    int vals[] = {61, 51, 16, 20, 55, 76, 85, 93, 65, 71, 81, 90, 101};

    /*
    Getting core dumped error when insertion requires a split of the root node. 
    Following are functions to look over and review. Issue occurred after refactoring
    raw pointers into smart pointers, specifically the shared_ptr's 

    Insert
	split()
		disconnectChild()
		removeItem()
		connectChild()
		getParent()
		insertItem()
		
	getParent()
	getNextChild()
	insertItem
	
double free issue occurs when vals[9] is inserted, we know it has to perform a split to rebalance the tree when inserting. 
    */
    
    t.Insert(vals[0]);
    t.Insert(vals[1]);
    t.Insert(vals[2]);
    t.Insert(vals[3]);
    t.Insert(vals[4]);
    t.Insert(vals[5]);
    t.Insert(vals[6]);
    t.Insert(vals[7]);
    t.Insert(vals[8]);
    t.Insert(vals[9]);

    t.recDisplay();


    // for (int val : vals)
    // {
    //     cout << "Inserting " << val << endl;    
    //     t.Insert(val);
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