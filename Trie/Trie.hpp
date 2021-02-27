#ifndef TRIE_HPP
#define TRIE_HPP
#include "Node.hpp"
#include <memory>

class Trie
{
private:
    std::shared_ptr<Node> root; 
public:
    Trie(/* args */);
    ~Trie();
    bool Insert(std::string word); 
    bool Search(std::string word);
};

Trie::Trie(/* args */)
{
    root = std::make_shared<Node>(Node());
}

Trie::~Trie()
{
}

bool Trie::Insert(std::string word)
{
    // TODO: think about when inserting word would fail. 

    Node* curr = root.get();
    
    for (auto letter : word)
    {
        letter = tolower(letter);

        if (!curr->letters[letter - 'a'])
        {
            curr->letters[letter - 'a'] = std::make_shared<Node>(Node());
        }

        curr = curr->letters[letter - 'a'].get(); 
    }

    curr->setIsWord(true);

    return true; 
}

bool Trie::Search(std::string word)
{
    Node* curr = root.get(); 
    for (auto letter : word)
    {
        letter = tolower(letter);

        if (!curr->letters[letter - 'a'])
        {
            return false;
        }

        curr = curr->letters[letter - 'a'].get();
    }

    return curr->getIsWord(); 
}


#endif