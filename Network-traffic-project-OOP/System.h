#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <vector>
#include <unordered_map>

#include "Stations.h"
#include "Lines.h"

using namespace std;

class System{
    public:
        System();
        void loadMenu();
        void loadFiles(const std::string& stations_file, const std::string& lines_file);
    private:
        void findRoute(int,int);
        void findRoute1(int,int);
        string findRoute2(int,int,bool);
        void clear();
        std::unordered_map<string, Lines*> lines_;
        std::unordered_map<int, Stations*> stations_;
        std::vector<Stations*> important_stations_;
};

#endif

