#include "Phonebook.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Exceptions.h"
using namespace std;
int aa=0;

Phonebook::Phonebook(): trie(new Trie()), selected_(""){}

void Phonebook::loadPhonebook(const string& filename){
    fstream newfile;
    newfile.open(filename, ios::in);
    string line;
    while(getline(newfile, line)){
        try{
        int pos = getComma(line);
        string name = line.substr(0, pos);
        string number = line.substr(pos+1);
        insert(name, number);}
        catch(FormatNotSupported*){}
    }
    newfile.close();
}

void Phonebook::insert(const string& name,const string& number){
    cout<<aa++<<endl;
    trie->insert(name,number);
}

int Phonebook::getComma(const string& line){
    for(int i=line.length();i>=0;i--){
        if(line[i] == ','){
            return i;
        }
    }
    throw new FormatNotSupported();
}

void Phonebook::search(const string& name){
    trie->search(name);
}

void Phonebook::addNew(){
    cout<<"Enter a name:"<<endl;
    string name;
    getline(cin, name);
    cout<<"Enter a number:"<<endl;
    string number;
    getline(cin, number);
    insert(name, number);
}

void Phonebook::select(const string& name){
    try{
        bool postoji=trie->thereIs(name);
        //if(postoji==1){   
            selected_=name;
            cout<<"Contact "<<name<<" selected"<<endl;
        //}
    }
    catch(NoContactFound*){
        cout<<"EXCEPTION : No such a contact"<<endl;
    }
    //else cout<<"No such a contact"<<endl;
}

void Phonebook::remove(){
    if(selected_==""){
        throw new NoContactSelected();
    }
    trie->deleteNode(selected_);
    selected_ = "";

}

void Phonebook::edit(const string& name,const string& number){
    if(name==""){
        trie->changenumber(selected_,number);
    }
    else if(number==""){
        trie->changename(selected_,name);
        selected_=name;
    }
    else{
        trie->deleteNode(selected_);
        trie->insert(name,number);
        selected_=name;
    }
}

void Phonebook::openTerminal()
{
    string input;
    cout<<" Enter a command:"<<endl<<endl;
    cout<<" 1.  NEW "<<endl<<endl;
    cout<<" 2.  SEARCH "<<endl<<endl;
    cout<<" 3.  SELECT "<<endl<<endl;
    cout<<" 4.  DELETE "<<endl<<endl;
    cout<<" 5.  EDIT "<<endl<<endl;
    cout<<" 6.  CALL "<<endl<<endl;
    cout<<" 7.  CALL HISTORY "<<endl<<endl; // display last 
    cout<<" 8.  EXIT "<<endl<<endl;
    while(true){
        getline(cin, input);
        if(input == "EXIT"){
            break;
        }
        else if(input=="NEW"){
            addNew();
        }
        else if(input.substr(0,6) == "SEARCH"){
            if(input.length() < 8){
                search("");
            }
            else{
                string name = input.substr(7);
                search(name);
            }
        }
        else if(input.substr(0,6) == "SELECT"){
            if(input.length() < 8){
                cout<<"No name entered"<<endl;
            }
            else{
                string name = input.substr(7);
                select(name);
            }
        }
        else if(input == "DELETE"){
            try{
                remove();
            }
            catch(NoContactSelected*){
                cout<<"EXCEPTION: Select contact that you want to delete"<<endl;
            }
            //if(selected_==""){
            //    cout<<"Please select a contact first"<<endl;
            //}
            //else{
            //    remove();
            //}
        }
        else if(input == "EDIT"){
            if(selected_.length() == 0){
                cout<<"Please select a contact first"<<endl;
            }
            else{
                cout<<"Select what do u want to edit : NAME | NUMBER | BOTH"<<endl;
                string what;
                getline(cin, what);
                if(what=="NAME"){
                    cout<<"Enter a new name :"<<endl;
                    string name;
                    getline(cin, name);
                    edit(name, "");
                }
                else if(what=="NUMBER"){
                    cout<<"Enter a new number:"<<endl;
                    string number;
                    getline(cin, number);
                    edit("", number);
                }
                else if(what=="BOTH"){
                    cout<<"Enter a new name:"<<endl;
                    string name;
                    getline(cin, name);
                    cout<<"Enter a new number:"<<endl;
                    string number;
                    getline(cin, number);
                    edit(name, number);
                }
                else{
                    cout<<"Invalid command"<<endl;
                }
            }
            
        }
        else if(input == "CALL"){
            if(selected_.length() == 0){
                cout<<"Please select a contact first"<<endl;
            }
            else{
                cout<<"Enter a name:"<<endl;
                string name;
                getline(cin, name);
                trie->call(selected_,name);
            }
        }
        else if(input == "CALL HISTORY"){
            trie->callHistory();
        }
        else{
            cout<<"Invalid command"<<endl;
        }
    }
}

Phonebook::~Phonebook(){
    delete trie;
}