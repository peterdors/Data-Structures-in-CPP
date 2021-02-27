#include "Trie.hpp"
#include <iostream>

int main(void)
{
    Trie trie; 
    trie.Insert("hello");
    trie.Insert("world");

    std::string word = "hello";
    std::cout << "Searching for word " << word << ": ";
    std::cout << trie.Search(word) << std::endl;

    return 0;
}