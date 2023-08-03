#include "Calls.h"
#include <iostream>
using namespace std;

Calls::Calls(const string& name1,const string& name2)
{
    name1_=name1;
    name2_=name2;
}

string Calls::getName1(){
    return name1_;
}

string Calls::getName2(){
    return name2_;
}

Calls::~Calls(){}