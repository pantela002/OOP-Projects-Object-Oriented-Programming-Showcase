#include <fstream>
#include "System.h"
#include "Stations.h"
#include <queue>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <stack>
#include "Exceptions.h"
using namespace std;

System::System(){}


void System::loadMenu(){
    while(true){
        cout<<"Welcome to the city transport network simulator. Please select an option:"<<endl;
        cout<<"1. Loading data"<<endl;
        cout<<"0. End of work"<<endl;
        int choice;
        cin>>choice;

        if(choice==1){
            cout<<"Enter the name of the station data file: ";
            string stations_file;
            cin>>stations_file;
            cout<<"Enter the name of the line data file: ";
            string lines_file;
            cin>>lines_file;
            loadFiles(stations_file, lines_file);
            
            while(true){
                int choice2;
                cout<<"Choose one option:"<<endl;
                cout<<"1. Display information about the stop list"<<endl;
                cout<<"2. Display of information about the city transport line"<<endl; 
                cout<<"3. Finding a path between 2 stops"<<endl;
                cout<<"4. End of work"<<endl;
                cin>>choice2;
                if(choice2==1){
                    cout<<"Enter stop ID: ";
                    int id;
                    cin>>id;
                    try{
                        if(stations_.find(id)==stations_.end())
                            throw new StationException("Station doesn't exist.");
                        else{
                            stations_[id]->infoStation();
                        }
                    }
                    catch(StationException*){
                        cout<<"Station doesn't exist."<<endl;
                    }
                }
                else if(choice2==2){
                    cout<<"Enter a line name: ";
                    string name;
                    cin>>name;
                    try{
                        if(lines_.find(name)==lines_.end())
                            throw new LineException("Line doesn't exist.");
                        else{
                            lines_[name]->infoLine();
                        }
                    }
                    catch(LineException*){
                        cout<<"Line doesn't exist."<<endl;
                    }
                }
                else if(choice2==3){
                    try{
                        int id1,id2;
                        cout<<"Enter the starting stop ID: ";
                        cin>>id1;
                        cout<<"Enter the ending stop ID: ";
                        cin>>id2; 
                        cout<<"Choose algorithm"<<endl;
                        int choice3;
                        cout<<"1. Any path"<<endl;
                        cout<<"2. The road with the fewest changes"<<endl;
                        cout<<"3. A road that goes around all important stations"<<endl;
                        cin>>choice3;
                        if(choice3==1)  findRoute(id1,id2);
                        else if( choice3==2) findRoute(id1,id2);
                        else if(choice3==3) findRoute1(id1,id2);
                    }
                    catch(StationException* s){
                        s->showMessage();
                    }
                    

                }
                else if(choice2==0){
                    cout<<"Have a great day !."<<endl;
                    clear();
                    break;
                }
                else{
                    cout<<"Unknown option."<<endl;
                }
            
            }
        
            
        }
        else if(choice==0){
            cout<<"Hvala na korištenju programa."<<endl;
            break;
        }
        else{
            cout<<"Nepoznata opcija."<<endl;
        }
    }
}

void System::loadFiles(const std::string& stations_file, const std::string& lines_file){
    fstream newfile;
    newfile.open(stations_file, ios::in);
    string row;
    while(getline(newfile, row)){
        int id = stoi(row.substr(0,row.find(' ')));
        string name = row.substr(row.find(' ')+1);
        bool important = false;
        int proba = name.length();
        if(name.find("[!]")!=-1){
            name = name.substr(0,name.find('[')-1);
            important = true;
        }
        //else{
        //    cout<<name<<endl;
        //}
        Stations* station = new Stations(id, name,important);
        stations_[id] = station;
    }
    newfile.close();
    newfile.open(lines_file, ios::in);
    while(getline(newfile, row)){
        Lines* line = new Lines(row.substr(0,row.find(' ')));
        string edit= row.substr(row.find(' ')+1);
        
        while(edit.empty()==false){
            int id = stoi(edit.substr(0,edit.find(' ')));
            line->addStation(stations_[id]);
            stations_[id]->addLine(line->getName());
            if(edit.find(' ')!=-1){
                edit = edit.substr(edit.find(' ')+1);
                int id1=stoi(edit.substr(0,edit.find(' ')));
                if(stations_[id]->existNode(id1)==false){
                    stations_[id]->addNode(stations_[id1]);
                }
                if(stations_[id1]->existNode(id)==false){
                    stations_[id1]->addNode(stations_[id]);
                }
            }
            else{
                break;
            }
        }
        lines_[line->getName()]=line;
    }
    newfile.close();

    for (auto l : lines_) {
        vector<Stations*> v_stations=l.second->getStations();
        for(int i=0; i<v_stations.size(); i++){
            for(int j=i+1; j<v_stations.size(); j++){
                v_stations[i]->addDirectNode(l.first, v_stations[j]);
                v_stations[j]->addDirectNode(l.first, v_stations[i]);
            }
        }
            
    }
    for( auto s : stations_){
        if(s.second->getImportant()==true){
            important_stations_.push_back(s.second);
        }
    }

    cout<<"Podaci su uspješno učitani."<<endl;
}


void System::findRoute(int start_id, int end_id){
    auto start_it = stations_.find(start_id);
    if (start_it == stations_.end()) {
        throw new StationException("Stajalište "+to_string(start_id)+" nije pronađeno.");
        //return;
    }
    auto end_it = stations_.find(end_id);
    if (end_it == stations_.end()) {
        throw new StationException("Stajalište"+to_string(end_id)+"nije pronađeno.");
        //return;
    }
    Stations* start = start_it->second;
    Stations* end = end_it->second;
    
    std::unordered_map<string,bool> visited;
    for(auto& line : lines_){
        visited[line.first] = false;
    }
    std::unordered_map<int,pair<Stations*,string>> t;
    for (auto s : stations_){
        t[s.second->getId()] = {nullptr,""};
    }
    std::queue<Stations*> queue;
    queue.push(start);
    while (!queue.empty()) {
        Stations* current = queue.front();
        queue.pop();
        if (t[end->getId()].first != nullptr) {
            //ovde
            string outputfile="files/putanja_"+to_string(start->getId())+"_"+to_string(end->getId())+".txt";
            ofstream newfile(outputfile, ios::out);
            Stations* prev=end;
            Stations* temps = t[end->getId()].first;
            string templ=t[end->getId()].second;
            string pom;
            stack <pair<pair<string,string>,string>> s;
            while(temps!=start){
                pom = lines_[templ]->makePath(temps,prev);
                prev=temps;
                s.push({{templ,t[temps->getId()].second},pom});
                templ=t[temps->getId()].second;
                temps=t[temps->getId()].first;
            }
            pom = lines_[templ]->makePath(temps,prev);
            s.push({{templ,""},pom});

            while(!s.empty()){
                newfile<<s.top().first.second<<"->"<<s.top().first.first<<endl;
                newfile<<s.top().second<<endl;
                s.pop();
            }

            break;
        //OVDE
        }



        for (auto& node : current->getNodes()) { 
            string prev=node.first;
            if (visited[prev] == false ) { 
                if(t[node.second->getId()].first==nullptr && node.second!=start){
                    t[node.second->getId()] = {current,prev};
                    queue.push(node.second);
                }
            }
        }
        for( auto& node : current->getNodes()){
            visited[node.first]=true;
        }
    }

}

void System::findRoute1(int start_id, int end_id){


    auto start_it = stations_.find(start_id);
    if (start_it == stations_.end()) {
        throw new StationException("Stajalište"+to_string(start_id)+"nije pronađeno.");
        //return;
    }
    auto end_it = stations_.find(end_id);
    if (end_it == stations_.end()) {
        throw new StationException("Stajalište"+to_string(end_id)+"nije pronađeno.");
        //return;
    }

    string outputfile="files/putanja_"+to_string(start_id)+"_"+to_string(end_id)+".txt";
    ofstream newfile(outputfile, ios::out);
    vector <Stations*> importantStations;
    importantStations.push_back(stations_[start_id]);
    for(auto s: important_stations_){
        if(s->getId()!=start_id && s->getId()!=end_id){
            importantStations.push_back(s);
        }
    }
    importantStations.push_back(stations_[end_id]);
    for(int i=0;i<importantStations.size()-1;i++){
            bool last=0;
            if(i==importantStations.size()-2) last =1; 
            string a=findRoute2(importantStations[i]->getId(),importantStations[i+1]->getId(),last);
            newfile<<a;
    }

}









string System::findRoute2(int start_id, int end_id,bool last){
    auto start_it = stations_.find(start_id);
    if (start_it == stations_.end()) {
        std::cout << "Error: No start station with ID " << start_id << " was found." << std::endl;
        return " ";
    }
    auto end_it = stations_.find(end_id);
    if (end_it == stations_.end()) {
        std::cout << "Error: No end station with ID " << end_id << " was found." << std::endl;
        return " ";
    }
    Stations* start = start_it->second;
    Stations* end = end_it->second;
    
    std::unordered_map<string,bool> visited;
    for(auto& line : lines_){
        visited[line.first] = false;
    }
    std::unordered_map<int,pair<Stations*,string>> t;
    for (auto s : stations_){
        t[s.second->getId()] = {nullptr,""};
    }
    std::queue<Stations*> queue;
    queue.push(start);
    while (!queue.empty()) {
        Stations* current = queue.front();
        queue.pop();
        if (t[end->getId()].first != nullptr) {
            //ovde
            string ispis="";
            Stations* prev=end;
            Stations* temps = t[end->getId()].first;
            string templ=t[end->getId()].second;
            string pom;
            stack <pair<pair<string,string>,string>> s;
            while(temps!=start){
                pom = lines_[templ]->makePath(temps,prev);
                prev=temps;
                s.push({{templ,t[temps->getId()].second},pom});
                templ=t[temps->getId()].second;
                temps=t[temps->getId()].first;
            }
            pom = lines_[templ]->makePath(temps,prev);
            s.push({{templ,""},pom});

            while(!s.empty()){
                ispis+=s.top().first.second+"->"+s.top().first.first+"\n";
                ispis+=s.top().second+"\n";
                if(s.size()==1 && last!=1) ispis+=s.top().first.first;
                s.pop();
            }
            return ispis;
        //OVDE
        }



        for (auto& node : current->getNodes()) { 
            string prev=node.first;
            if (visited[prev] == false ) { 
                if(t[node.second->getId()].first==nullptr && node.second!=start){
                    t[node.second->getId()] = {current,prev};
                    queue.push(node.second);
                }
            }
        }
        for( auto& node : current->getNodes()){
            visited[node.first]=true;
        }
    }
    return " ";

}

void System::clear(){
    for(auto& line : lines_){
        delete line.second;
    }
    for(auto& station : stations_){
        delete station.second;
    }
    
}
