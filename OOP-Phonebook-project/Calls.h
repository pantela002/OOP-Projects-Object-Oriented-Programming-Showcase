#ifndef CALLS_H
#define CALLS_H


#include <iostream>
#include <string>

using namespace std;

class Calls{
public:
    Calls(const string& name1,const string& name2);
    string getName1();
    string getName2();
    ~Calls();
private:
    string name1_;
    string name2_;
};

#endif