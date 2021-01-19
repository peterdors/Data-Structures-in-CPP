#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include <memory>
#include <iostream>
#include <vector>

using namespace std; 

template <class T> 
class Tree
{
private:
    Node<T>* root; 
    // unique_ptr<Node<T>> root; 
    vector<Node<T>*> markedNodes;
    vector<Data<T>*> markedData;

    Node<T>* getNextChild(Node<T>* node, T val)
    {
        int i;
        for (i = 0; i < node->numItems; i++)
        {
            if (
                // node->vals[i] != nullptr && 
            val < node->vals[i]->val)
            {
                return node->childs[i];
            }
        }

        return node->childs[i];
    }

    void split(Node<T>* currNode)
    {
        Data<T>* itemB, *itemC; 
        Node<T>* parent, *child2, *child3; 

        itemC = currNode->removeItem();
        itemB = currNode->removeItem(); 

        child2 = currNode->disconnectChild(2);
        child3 = currNode->disconnectChild(3);

        Node<T>* newRight = new Node<T>();

        if (currNode == root)
        {
            root = new Node<T>(); 
            parent = root; 
            root->connectChild(0, currNode);
        }
        else
        {
            parent = currNode->getParent();
        }

        int itemIndex = parent->insertItem(itemB);
        int n = parent->numItems;

        for (int i = n-1; i > itemIndex; i--)
        {
            Node<T>* temp = parent->disconnectChild(i);
            parent->connectChild(i+1, temp);
        }

        parent->connectChild(itemIndex + 1, newRight);

        newRight->insertItem(itemC);
        newRight->connectChild(0, child2);
        newRight->connectChild(1, child3);   
    }


    void recDisplay(Node<T>* curr, int level, int childNum)
    {
        if (curr == nullptr)
        {

            return;
        }

        cout << "Level: " << level << ", child: " << childNum << ", nodes: (";
        for (int i = 0; i < curr->numItems; i++)
        {
            cout << curr->vals[i]->val << ", ";
        }
        cout << ")" << endl;

        for (int i = 0; i < curr->numItems + 1; i++)
        {
            Node<T>* next = curr->childs[i]; 
            if (next == nullptr)
            {
                return;
            }

            recDisplay(next, level+1, i);
        }
    }

    void inorderDisplay(Node<T>* curr, int level, int childNum)
    {
        int n = curr->numItems; 


        for (int i = 0; i < n + 1; i++)
        {
            Node<T>* child = curr->childs[i];

            if (child != nullptr)
            {
                inorderDisplay(child, level + 1, i);
            }
            else
            {

        cout << "Level " << level << ": ";
                for (int j = 0; j < curr->numItems; j++)
                {
                    
                    cout << curr->vals[j]->val << ", "; 
                }

                return;
            }

            // if (i < n)
            // {
            //     cout << curr->vals[i]->val << ", ";
            // }
            
        }
    }
    
    // bool Search(T val, Node<T>* node)
    Node<T>* Search(T val, Node<T>* node)
    {
        if (node == nullptr) 
        {
            return nullptr;
        }

        // numItems indicative of the number of values stored at the current node.
        for (int i = 0; i < node->numItems; i++)
        {
            T currVal = node->vals[i]->val;
            if (val == currVal) 
            {
                // return true;
                return node; 
            }

            else if (val < currVal)
            {
                // recurse adjacent subtree
                return Search(val, node->childs[i]);
            }
        }

        return Search(val, node->childs[node->numItems]);
    }

    void ForestFire(Node<T>* node)
    {
        if (node == nullptr)
        {
            return; 
        }

        for (int i = 0; i < node->numItems + 1; i++)
        {
            if (i < node->numItems)
            {
                delete node->vals[i]; 

            }

            ForestFire(node->childs[i]);
            delete node->childs[i];
        }

        // if (node != nullptr)
        //     delete node;
    }

    Node<T>* deleteLeafCases(Node<T>* node, T val)
    {
        char sibling_side = 'l';
        Node<T>* p = node->getParent();
        Node<T>* sibling = node->getSibling(val);

        if (sibling == nullptr)
        {
            sibling_side = 'r';
            sibling = p->childs[1];
        }

        if (sibling && sibling->numItems == 1)
        {
            for (int i = 0; i <= p->numItems; i++)
            {
                if (p->childs[i] == sibling && sibling_side == 'l')
                {
                    // delete node->vals[node->numItems-1]; 
                    markedData.push_back(node->vals[node->numItems-1]);
                    node->vals[node->numItems-1] = nullptr;
                    node->numItems = node->numItems - 1;
                    Data<T>* d = p->vals[i];
                    sibling->insertItem(d);
                    p->disconnectChild(i + 1);

                    for (int j = i; j < p->numItems; j++)
                    {
                        if (j + 1 < p->numItems)
                        {
                            p->vals[j] = p->vals[j+1];
                            if (j + 2 <= p->numItems)
                            {
                                p->connectChild(j + 1, p->disconnectChild(j + 2));
                            }
                        }
                    }

                    // delete p->vals[p->numItems-1];
                    markedData.push_back(p->vals[p->numItems-1]);
                    p->vals[p->numItems-1] = nullptr;
                    p->numItems = p->numItems - 1;

                    if (p->numItems == 0)
                    {
                        if (p != root)
                        {
                            p = balanceTree(p); 
                        }
                        else
                        {
                            root = sibling;
                        }
                        
                    }

                    return p;
                }
                else if (p->childs[i] == sibling && sibling_side == 'r')
                {
                    // delete node->vals[node->numItems - 1];
                    markedData.push_back(node->vals[node->numItems - 1]);
                    node->vals[node->numItems - 1] = nullptr;
                    node->numItems = node->numItems - 1; 
                    Data<T>* d = p->vals[i-1];
                    sibling->insertItem(d);
                    p->disconnectChild(0);
                    p->connectChild(0, p->disconnectChild(1));

                    for (int j = i; j < p->numItems; j++)
                    {
                        p->vals[j-1] = p->vals[j];
                        if (j + 1 <= p->numItems)
                        {
                            p->connectChild(j, p->disconnectChild(j+1));
                        }
                    }

                    // delete p->vals[p->numItems - 1];
                    markedData.push_back(p->vals[p->numItems - 1]);
                    p->vals[p->numItems - 1] = nullptr; 
                    p->numItems = p->numItems - 1; 

                    if (p->numItems == 0)
                    {
                        if (p != root)
                        {
                            p = balanceTree(p);
                        }
                        else
                        {
                            root = sibling;
                        }
                        
                    }

                    return p;
                }
            
            }
        }
        else if (sibling && sibling->numItems > 1)
        {
            int f = 0; 
            if (sibling_side == 'r')
            {
                f = 0; 
            }
            else 
            {
                f = sibling->numItems - 1;
            }

            for (int i = 0; i <= p->numItems; i++)
            {
                if (p->childs[i] == sibling && sibling_side == 'l')
                {
                    node->vals[0]->val = p->vals[i]->val;
                    p->vals[i]->val = sibling->vals[f]->val;
                    sibling->deleteNodeValue(sibling->vals[f]->val);
                    return p;
                }
                if (p->childs[i] == sibling && sibling_side == 'r')
                {
                    node->vals[0]->val = p->vals[i-1]->val;
                    p->vals[i-1]->val = sibling->vals[f]->val;
                    sibling->deleteNodeValue(sibling->vals[f]->val);
                    return p;
                }
                
            }
        }
        
        root = new Node<T>();
        return node;
    }

    Node<T>* balanceTree(Node<T>* node)
    {
        char siblingSide = 'l';
        Node<T>* p = node->getParent(); 
        Node<T>* sibling = node->getSibling(-1); 

        if (sibling == nullptr)
        {
            siblingSide = 'r';
            sibling = p->childs[1];
        }

        if (sibling->numItems == 1)
        {
            for (int i = 0; i <= p->numItems; i++)
            {
                if (p->childs[i] == sibling && siblingSide == 'l')
                {
                    // Merge parent and child and remove parent
                    Data<T>* d = p->vals[i]; 
                    sibling->insertItem(d);

                    sibling->connectChild(sibling->numItems, node->disconnectChild(0));
                    p->disconnectChild(i+1);

                    for (int j = i; j < p->numItems; j++)
                    {
                        if (j + 1 < p->numItems)
                        {
                            p->vals[j] = p->vals[j+1];
                            if (j + 2 <= p->numItems)
                            {
                                p->connectChild(j+1, p->disconnectChild(j+2));
                            }
                        }
                    }

                    // delete p->vals[p->numItems - 1];
                    markedData.push_back(p->vals[p->numItems - 1]);
                    p->vals[p->numItems - 1] = nullptr; 
                    p->numItems = p->numItems - 1; 

                    if (p->numItems == 0)
                    {
                        if (p != root)
                        {
                            p = balanceTree(p);
                        }
                        else
                        {
                            root = sibling;
                        }
                        
                    }
                    return p;
                }
                else if (p->childs[i] == sibling && siblingSide == 'r')
                {
                    Data<T>* d = p->vals[i-1];
                    sibling->insertAtFront(d); // todo
                    sibling->connectChild(0, node->disconnectChild(0));
                    p->disconnectChild(0);
                    p->connectChild(0, p->disconnectChild(1));

                    for (int j = i; j < p->numItems; j++)
                    {
                        p->vals[j-1] = p->vals[j];
                        if (j + 1 <= p->numItems)
                        {
                            p->connectChild(j, p->disconnectChild(j+1));
                        }
                    }

                    // delete p->vals[p->numItems - 1];
                    markedData.push_back(p->vals[p->numItems - 1]);
                    p->vals[p->numItems - 1] = nullptr; 
                    p->numItems = p->numItems - 1;

                    if (p->numItems == 0)
                    {
                        if (p != root)
                        {
                            p = balanceTree(p);
                        }
                        else
                        {
                            root = sibling;
                        }
                        
                    }

                    return p;
                }
            }
        }
        else if (sibling->numItems > 1)
        {
            int f = 0; 
            if (siblingSide == 'r')
            {
                f = 0; 
            }
            else
            {
                f = sibling->numItems - 1;
            }

            for (int i = 0; i <= p->numItems; i++)
            {
                if (p->childs[i] == sibling && siblingSide == 'l')
                {
                    node->numItems = node->numItems - 1;
                    node->connectChild(1, node->disconnectChild(0));
                    node->connectChild(0, sibling->disconnectChild(sibling->numItems));
                    node->vals[0] = p->vals[i];

                    p->vals[i] = sibling->vals[f];

                    // delete sibling->vals[sibling->numItems - 1];
                    markedData.push_back(sibling->vals[sibling->numItems - 1]);
                    sibling->vals[sibling->numItems - 1] = nullptr;
                    sibling->numItems = sibling->numItems - 1;

                    return p;
                }

                if (p->childs[i] == sibling && siblingSide == 'r')
                {
                    node->numItems = node->numItems + 1; 
                    node->vals[0] = p->vals[i-1];
                    p->vals[i-1] = sibling->vals[f];
                    node->connectChild(1, sibling->disconnectChild(f));

                    for (int j = 0; j < sibling->numItems; j++)
                    {
                        if (j + 1 < sibling->numItems)
                        {
                            sibling->vals[j] = sibling->vals[j+1];
                        }
                        sibling->connectChild(j, sibling->disconnectChild(j+1));
                    }

                    // delete sibling->vals[sibling->numItems - 1];
                    markedData.push_back(sibling->vals[sibling->numItems - 1]);
                    sibling->vals[sibling->numItems - 1] = nullptr;
                    sibling->numItems = sibling->numItems - 1;

                    return p;
                }
            }
        }

        return nullptr;
    }
    
public:
    Tree()
    {
        root = new Node<T>(); 
    }

    ~Tree()
    {
        ForestFire(root);
        delete root;
    }

    void Insert(const T& val)
    {
        Node<T>* curr = root;
        Data<T>* data = new Data<T>(val);

        while (true)
        {
            if (curr->isFull())
            {
                split(curr); 
                curr = curr->getParent();
                curr = getNextChild(curr, val);
            }
            else if (curr->isLeaf())
            {
                break; // maybe use in while conditional? 
            }
            else
            {
                curr = getNextChild(curr, val);
            }
            
        }

        curr->insertItem(data); 
    }

    bool Search(const T& val)
    {
        Node<T>* node = Search(val, root); 
        return node != nullptr;

        // return Search(val, root);
    }

    bool Remove(const T& val)
    {
        // root = Remove(root, val);
        // return root != nullptr;

        Node<T>* res = Remove(root, val);

        // while (!markedData.empty())    
        // {
        //     Data<T>* temp = markedData.front();
        //     markedData.pop_back();
        //     if (temp)
        //     {
        //         cout << "Deleting " << temp->val << endl;
        //         delete temp;
        //     }
            
        // }

        return res != nullptr;
    }

    Node<T>* Remove(Node<T>* root, const T& val)
    {
        Node<T>* node = Search(val, root);

        if (node == nullptr)
        {
            return node;
        }

        // if (node->isSingleNodeInTree())
        // {
        //     node = new Node<T>();
        //     return node;
        // }

        if (node->isLeaf())
        {
            if (node->numItems > 1)
            {
                node->deleteNodeValue(val);
                return node;
            }
            else
            {
                Node<T>* y = deleteLeafCases(node, val);
                return y;
            }
        }
        else
        {
            Node<T>* n = getNextChild(node, val);
            Node<T>* c = getInorderNode(n);

            Data<T>* d = c->vals[0];
            int k = d->val;
            Remove(c, k);

            Node<T>* found = Search(val, root);
            // Segfault occurs here when using delete and marking pointers to nullptr.
            for (int i = 0; i < found->numItems; i++)
            {
                if (found->vals[i]->val == val)
                {
                    found->vals[i]->val = k;
                }
            }

            return found;
        }
        

        return nullptr;
    }

    Node<T>* getInorderNode(Node<T>* node)
    {
        Node<T>* c = nullptr; 
        if (node->isLeaf())
        {
            c = node;
        }
        else 
        {
            c = getInorderNode(node->childs[0]);
        }

        return c;
    }

    void inorder()
    {
        inorderDisplay(root, 0, 0);
        cout << endl;
    }

    void recDisplay()
    {
        recDisplay(root, 0, 0);
    }

};





#endif