#ifndef NODE_HPP
#define NODE_HPP

#include <memory>

#define ALPHABET_SIZE 26
struct Node
{
    bool isWord;
    std::shared_ptr<Node> letters[ALPHABET_SIZE];

    Node()
    {
        isWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            letters[i] = nullptr;
        }
    }

    void setIsWord(bool val)
    {
        this->isWord = val;
    }

    bool getIsWord()
    {
        return this->isWord;
    }

    // std::shared_ptr<Node> getLetters()
    // {
    //     return letters;
    // }
};



#endif