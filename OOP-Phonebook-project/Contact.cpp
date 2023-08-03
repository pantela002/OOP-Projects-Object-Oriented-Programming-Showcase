#include "Contact.h"

Contact::Contact(const string& name,const string& number): name_(name), number_(number){}

string Contact::getName() const{
    return name_;
}

string Contact::getNumber() const{
    return number_;
}

void Contact::setNumber(const string& number){
    number_=number;
}

void Contact::setName(const string& name){
    name_ = name;
}

