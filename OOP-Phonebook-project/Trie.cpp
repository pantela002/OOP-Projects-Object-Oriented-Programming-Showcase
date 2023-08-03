#include "Trie.h"
#include "Trienode.h"
#include "Calls.h"
#include <iostream>
#include <string>
#include "Exceptions.h"
using namespace std;


int Trie::count = 0;

Trie::Trie(): root(new TrieNode()){}

int Trie::find(const char& c){
    if((c<='z' && c>='a')){
        return c-'a';
    }
    else if(c<='Z' && c>='A'){
        return c-'A';
    }
    else{
        return 26;
    }

}

void Trie::exist(const string& word){
    TrieNode* current = root;
    for(int i=0;i<word.length();i++){
        int index = find(word[i]);
        if(current->getChildren(index) == nullptr){
            return ;
        }
        current = current->getChildren(index);
    }
    if(current->getIsEndOfWord()){
        throw new NoContactSelected();
    }
    else{
        return ;
    }
}

int Trie::thereIs(const string& word){
    TrieNode* current = root;
    for(int i=0;i<word.length();i++){
        int index = find(word[i]);
        if(current->getChildren(index) == nullptr){
            throw new NoContactFound();
            //return 0;
        }
        current = current->getChildren(index);
    }
    if(current->getIsEndOfWord()){
        return 1;
    }
    else{
        throw new NoContactFound();
    }
}

void Trie::insert(const string& word,const string& number){
    try{
        exist(word);
        TrieNode* current = root;
        for(int i=0;i<word.length();i++){
            int index = find(word[i]);
            if(current->getChildren(index)==nullptr){
                current->setChildren(index,new TrieNode());
            }
            current = current->getChildren(index);
        }
        current->setIsEndOfWord(true);
        current->setContact(new Contact(word,number));

    }
    catch(NoContactSelected*){
        cout<<"Contact already exists"<<endl;
    }
}

void Trie::search(const string& word){
    TrieNode* current = root;
    for(int i=0;i<word.length();i++){
        int index = find(word[i]);
        if(current->getChildren(index) == nullptr){
            cout<<"Not found"<<endl;
            return;
        }
        current = current->getChildren(index);
    }
    printall(current);
    
}

void Trie::printall(TrieNode* current){
    for(int i=0;i<SIZE;i++){
        if(current->getChildren(i) != nullptr){
            printall(current->getChildren(i));
        }
    }
    if(current->getIsEndOfWord()){
        cout<<current->getContact()->getName()<<"  :  "<<current->getContact()->getNumber()<<endl;
    }
}

void Trie::deleteNode(const string& word){
    TrieNode* current = root;
    for(int i=0;i<word.size();i++){
        int index = this->find(word[i]);
        TrieNode* pom = current;
        justone(pom->getChildren(index));
        if(count>1){
            if(i==word.size()-1){
                cout<<word[i];
                current->getChildren(index)->setIsEndOfWord(false);
            }else{
                count=0;
                current = current->getChildren(index);
            }
        }
        else{
            remove(current,word.substr(i,word.size()-i));
            return;
        }
    }
    
}

void Trie::justone(TrieNode* current){
    for(int i=0;i<SIZE;i++){
        if(current->getChildren(i) != nullptr){
            justone(current->getChildren(i));
        }
    }
    if(current->getIsEndOfWord()){
        count++;
    }
}

void Trie::remove(TrieNode* current,const string& word){
    TrieNode* pom1 = current->getChildren(find(word[0]));
    current->setChildren(find(word[0]),nullptr);
    TrieNode* pom2=nullptr;
    for(int i=1;i<word.size();i++){
        int index = find(word[i]);
        pom2=pom1;
        pom1=pom1->getChildren(index);
        delete pom2;
    }
    delete pom1;
}

void Trie::changenumber(const string& selected,const string& number){
    TrieNode* current = root;
    for(int i=0;i<selected.length();i++){
        int index = find(selected[i]);
        current = current->getChildren(index);
    }
    current->getContact()->setNumber(number);
} //hmm

void Trie::changename(const string& selected,const string& word){
    TrieNode* current = root;
    for(int i=0;i<selected.length();i++){
        int index = find(selected[i]);
        current = current->getChildren(index);
    }
    string number=current->getContact()->getNumber();
    deleteNode(selected);
    insert(word,number);
}

void Trie::call(const string& selected,const string& name){
    TrieNode* current = root;
    for(int i=0;i<name.length();i++){
        int index = this->find(name[i]);
        current = current->getChildren(index);
    }
    if(current->getIsEndOfWord()){
        cout<<"Calling "<<name<<endl;
        if(q.size()==10){
            q.pop();
            q.push(new Calls(selected,name));
        }
        else if(q.size()<10){
            q.push(new Calls(selected,name));
        }
    }
    else{
        cout<<"Contact "<<name<<" Not found"<<endl;
    }
}

void Trie::callHistory(){
    queue<Calls*> pom;
    while(!q.empty()){
        pom.push(q.front());
        q.pop();
    }
    while(!pom.empty()){
        cout<<pom.front()->getName1()<<" "<<pom.front()->getName2()<<endl;
        q.push(pom.front());
        pom.pop();
    }
}

Trie::~Trie(){
    destructor(root);
}

void Trie::destructor(TrieNode* current){
    Calls* pom=nullptr;
    while(!q.empty()){
        pom=q.front();
        q.pop();
        delete pom;
    }
    for(int i=0;i<SIZE;i++){
        if(current->getChildren(i) != nullptr){
            destructor(current->getChildren(i));
        }
    }
    current->deleteContact();
}








