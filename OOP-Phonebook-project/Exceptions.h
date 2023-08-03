#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <iostream>
#include <exception>
using namespace std;

class FormatNotSupported : public exception{
public:
    FormatNotSupported() : exception() {
        cout<<"EXCEPTION : Format not supported in load data"<<endl;
    }
};

class NoContactSelected : public exception{
public:
    NoContactSelected() : exception() {}
};

class NoContactFound : public exception{
public:
    NoContactFound() : exception() {}
};
#endif