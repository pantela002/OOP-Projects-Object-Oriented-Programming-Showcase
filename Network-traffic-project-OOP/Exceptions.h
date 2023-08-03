#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>

using namespace std;

class StationException {
	string message;
public:
	StationException(const string &poruka);
	string showMessage() const;
};

class LineException {
	string message;
public:
	LineException(const string &poruka);
	string showMessage() const;
};


#endif
