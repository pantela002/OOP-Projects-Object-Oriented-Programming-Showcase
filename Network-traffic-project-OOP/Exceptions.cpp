#include "Exceptions.h"

StationException::StationException(const string &poruka) : message(poruka) {

}

string StationException::showMessage() const {
    cout<<"StationException: "<<message<<endl;
	return message;
}


LineException::LineException(const string &poruka) : message(poruka) {

}

string LineException::showMessage() const {
    cout<<"LineException: "<<message<<endl;
	return message;
}
