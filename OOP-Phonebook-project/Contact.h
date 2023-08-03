#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>

using namespace std;

class Contact{
public:
    Contact(const string& name, const string& number);
    string getName() const;
    string getNumber() const;
    void setNumber(const string& number);
    void setName(const string& name);

private:
    string name_;
    string number_;
};


#endif