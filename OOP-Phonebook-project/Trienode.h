#ifndef TRIENODE_H
#define TRIENODE_H
#include "Contact.h"
#include <iostream>
using namespace std;

class TrieNode{
public:
    TrieNode();
    TrieNode* getChildren(int index) const;
    bool getIsEndOfWord() const;
    void setChildren(int index, TrieNode* node);
    void setIsEndOfWord(bool isEnd);
    Contact* getContact() const;
    void setContact(Contact* contact);
    ~TrieNode();
    void deleteContact();
private:
    static const int SIZE=27;
    Contact* contact_;
    TrieNode* children_[SIZE];
    bool isEndOfWord_;

};

#endif