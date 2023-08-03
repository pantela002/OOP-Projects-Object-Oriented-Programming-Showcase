#ifndef LINES_H
#define LINES_H

#include <iostream>
#include <vector>
#include "Stations.h"
using namespace std;

class Lines{

public:
    
    Lines(const string&);
    Lines(const Lines&) = delete;
    Lines(Lines&&) = delete;
    string getName();
    void addStation(Stations*);
    string makePath(Stations* start,Stations* end);
    void infoLine();
    vector<Stations*> getStations();
    ~Lines();

private:
    string name_;
    vector<Stations*> stations_;

};

#endif

