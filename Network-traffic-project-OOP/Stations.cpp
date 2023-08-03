#include "Stations.h"
#include <fstream>
#include <algorithm>
using namespace std;
Stations::Stations(int id, const string& naziv,bool important): id_(id), naziv_(naziv), important_(important) {}

int Stations::getId(){
    return id_;
}

string Stations::getNaziv(){
    return naziv_;
}

void Stations::addNode(Stations* node){
    neighbours_.push_back(node);
}

bool Stations::getImportant(){
    return important_;
}

bool Stations::existNode(int node){
    for(int i=0; i<neighbours_.size(); i++){
        if(neighbours_[i]->getId()==node){
            return true;
        }
    }
    return false;
}


void Stations::addLine(const string& line){
    line_names_.push_back(line);
}

void Stations::infoStation(){

    string outputfile="files/stajaliste_"+to_string(id_)+".txt";
    ofstream newfile(outputfile, ios::out);

    newfile<<id_<<" "<<naziv_.substr(0,naziv_.size()-1)<<" [";
    sort(line_names_.begin(), line_names_.end());
    for(int i=0; i<line_names_.size()-1; i++){
        newfile<<line_names_[i]<<" ";
    }
    newfile<<line_names_[line_names_.size()-1]<<"]";
    newfile<<" {! ";
    for(int i=0; i<neighbours_.size(); i++){
        if(neighbours_[i]->getImportant()==true){
            newfile<<neighbours_[i]->getId()<<" ";
        }
    }
    newfile<<"!}";

}


void Stations::addDirectNode(const string& line, Stations* node){
    pair<string,Stations*> new_node;
    new_node.first=line;
    new_node.second=node;
    direct_neighbours_.push_back(new_node);
}


vector<pair<string,Stations*>> Stations::getNodes(){
    return direct_neighbours_;
}

Stations::~Stations() {}