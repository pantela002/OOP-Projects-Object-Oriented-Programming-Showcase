#include <iostream>
#include <string>
#include <vector>
#include "Phonebook.h"
using namespace std;

int main(){

    Phonebook* phonebook =new  Phonebook();
    phonebook->loadPhonebook("tst.csv");
    phonebook->openTerminal();
    int wa;
    cin>>wa;
    cout<<" ";
    return 0;
}