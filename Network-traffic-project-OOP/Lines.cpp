#include "Lines.h"
#include <fstream>
Lines::Lines(const string& name):  name_(name) {}

string Lines::getName(){
    return name_;
}

void Lines::addStation(Stations* station){
    stations_.push_back(station);
}

void Lines::infoLine(){
    ofstream newfile("files/linija_"+name_+".txt", ios::out);
    newfile<<name_<<" "<<stations_[0]->getNaziv().substr(0,stations_[0]->getNaziv().size()-1)<<"->"<<stations_[stations_.size()-1]->getNaziv()<<endl;
    for(int i=0; i<stations_.size(); i++){
        newfile<<stations_[i]->getId()<<" "<<stations_[i]->getNaziv();
        if(stations_[i]->getImportant()==true){
            newfile<<" [!]";
        }
        newfile<<endl;
    }
}


string Lines::makePath(Stations* start,Stations* end){
    string path="";
    int start_index=0;
    int end_index=0;
    for(int i=0; i<stations_.size(); i++){
        if(stations_[i]->getId()==start->getId()){
            start_index=i;
        }
        if(stations_[i]->getId()==end->getId()){
            end_index=i;
        }
    }
    if(start_index<end_index){
        for(int i=start_index; i<=end_index; i++){
            path+=to_string(stations_[i]->getId())+" ";
        }
    }
    else{
        for(int i=start_index; i>=end_index; i--){
            path+=to_string(stations_[i]->getId())+" ";
        }
    }
    return path;
}

vector<Stations*> Lines::getStations(){
    return stations_;
}

Lines::~Lines() {}