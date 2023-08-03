#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <queue>

#include "Trienode.h"
#include "Calls.h"
using namespace std;


class Trie{

public:
    Trie();
    int find(const char& c);
    void insert(const string& word,const string& number);
    void search(const string& word);
    void printall(TrieNode* current);
    void exist(const string& word);
    void deleteNode(const string& word);
    void justone(TrieNode* current);
    void remove(TrieNode* current,const string& word);
    void changename(const string& selected,const string& word);
    void changenumber(const string& selected,const string& number);
    void call(const string& selected,const string& name);
    void callHistory();
    int thereIs(const string& word);
    void destructor(TrieNode* current);
    ~Trie();
private:
    TrieNode* root;
    static const int SIZE = 27;
    static int count;
    queue<Calls*> q;
};

#endif