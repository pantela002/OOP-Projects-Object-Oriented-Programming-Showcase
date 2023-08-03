#include "Trienode.h"
#include <iostream>
#include <string>
using namespace std;



TrieNode::TrieNode():isEndOfWord_(false),contact_(nullptr){
    for(int i=0;i<SIZE;i++){  // -26 ako hocu da ubacim samo mala slova
        children_[i] = nullptr;
    }
}

TrieNode* TrieNode::getChildren(int index) const{
    return children_[index];
}

bool TrieNode::getIsEndOfWord() const {
    return isEndOfWord_;
}

void TrieNode::setIsEndOfWord(bool isEnd){
    isEndOfWord_ = isEnd;
}

void TrieNode::setChildren(int index, TrieNode* node){
    children_[index] = node;
}

Contact* TrieNode::getContact() const{
    return contact_;
}

void TrieNode::setContact(Contact* contact){
    contact_ = contact;
}

TrieNode::~TrieNode(){
}

void TrieNode::deleteContact(){
    delete contact_;
    delete [] children_;
}

