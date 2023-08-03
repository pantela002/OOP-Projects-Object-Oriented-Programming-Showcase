#ifndef STATIONS_H
#define STATIONS_H
#include <iostream>
#include <vector>
using namespace std;


class Stations{
    public: 
        Stations(int,const string&,bool);
        Stations(const Stations&);
        Stations(Stations&&) = delete;
        void addNode(Stations*);
        void addDirectNode(const string&,Stations*);
        void infoStation();
        void addLine(const string&);
        vector <pair<string,Stations*>> getNodes();
        int getId();
        bool existNode(int);
        string getNaziv();
        bool getImportant();
        ~Stations();
    private:
        int id_;
        string naziv_;
        bool important_;
        vector <Stations*> neighbours_;
        vector <pair<string,Stations*>> direct_neighbours_;
        vector <string> line_names_;
};

#endif

