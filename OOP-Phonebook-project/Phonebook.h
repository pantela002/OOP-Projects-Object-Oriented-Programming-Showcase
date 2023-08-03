#ifndef PHONEBOOK_H
#define PHONEBOOK_H
#include <string>
#include <iostream>
#include "Trie.h"

using namespace std;

class Phonebook{
public:
    Phonebook();
    void loadPhonebook(const string& filename);
    int getComma(const string& line);
    void openTerminal();
    void insert(const string& name,const string& number);
    void search(const string& name);
    void addNew();
    void select(const string& name);
    void remove();
    void edit(const string& name,const string& number);
    ~Phonebook();
private:
    Trie* trie;
    string selected_;
};

#endif

