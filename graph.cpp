// JAI BAJRANGBALI

#include<bits/stdc++.h>
using namespace std;

class Graph {
    private:
        unordered_map<string,list<pair<string,int>>> vertices;
        unordered_map<string,string> stationMapping;

    public:

        Graph() {
            stationMapping = {
                {"GP","Govindpuri(GP)"},
                {"KM","Kalkaji Mandir(KM)"},
                {"LN", "Lajpat Nagar(LN)"},
                {"NE", "Nehru Enclave(NE)"},
                {"IIT", "IIT(IIT)"},
                {"HK", "Hauz Khas(HK)"},
                {"IGIT1", "IGI Terminal 1(IGIT1)"},
                {"HCC", "Huda City Center(HCC)"}
            };
        }

        void addVertex(string code) {
            string name = stationMapping[code];
            if(!name.empty()) {
                vertices[name] = list<pair<string,int>>();
            }
            else {
                cout<<"Invalid station code"<<endl;
            }
        }

        void addEdge(string code1, string code2, int weight) {
            //as travelling in both directions is possible, the graph is gonna be an undirected one
            string name1 = stationMapping[code1];
            string name2 = stationMapping[code2];

            if(!name1.empty() && !name2.empty()) {
                vertices[name1].push_back(make_pair(name2,weight));
                vertices[name2].push_back(make_pair(name1,weight));
            }
            else {
                cout<<"Invalid station code"<<endl;
            }
        }

        void showStations() {
            for(auto station: vertices) {
                cout<<station.first<<endl;
            }
        }

        void showMetroMap() {
            for(auto station: vertices) {
                cout<<station.first<<"->";
                for(auto nbr: station.second) {
                    cout<<"("<<nbr.first<<", "<<nbr.second<<"), ";
                }
                cout<<endl;
            }
        }

        void minimumCostDjikstra(string srcCode,string destCode) {
            
            string srcStation = stationMapping[srcCode];
            string destStation = stationMapping[destCode];

            if(srcStation.empty() || destStation.empty()) {
                cout<<"\nEither source or destination code is invalid\n\n";
                return;
            }

            unordered_map<string,int> stationIndices;
            int index = 0;
            for(auto &i: vertices) {
                string node = i.first;
                stationIndices[node]=index++;
            }

            int n = vertices.size()+1;
            vector<int> dist(n,INT_MAX);
            set<pair<int,string>> s;

            dist[stationIndices[srcStation]]=0;
            s.insert(make_pair(0,srcStation));

            while(!s.empty()) {
                auto top = *(s.begin());
                int stationDist = top.first;
                string stationName = top.second;

                s.erase(s.begin());

                for(auto nbr: vertices[stationName]) {
                    int nbrIdx = stationIndices[nbr.first];
                    if(stationDist+nbr.second<dist[nbrIdx]) {
                        auto res = s.find(make_pair(dist[nbrIdx],nbr.first));
                        if(res!=s.end()) {
                            s.erase(res);
                        }
                        dist[nbrIdx]=stationDist+nbr.second;
                        s.insert(make_pair(dist[nbrIdx],nbr.first));
                    }
                }
            }
            cout<<"\nThe minimum cost to travel from "<<srcStation<<" to "<<destStation<<" is "<<dist[stationIndices[destStation]]<<" rupees.\n\n";
        }
};

void menu() {

    Graph g;
    g.addVertex("GP");
    g.addVertex("KM");
    g.addVertex("LN");
    g.addVertex("NE");
    g.addVertex("IIT");
    g.addVertex("HK");
    g.addVertex("IGIT1");
    g.addVertex("HCC");

    g.addEdge("GP","KM",20);
    g.addEdge("KM","LN",25);
    g.addEdge("LN","NE",35);
    g.addEdge("NE","IIT",40);
    g.addEdge("IIT","HK",20);
    g.addEdge("IIT","IGIT1",50);
    g.addEdge("HK","HCC",45);
    
    cout<<"\n\t\t\t\t\t\tWELCOME TO METRO APP\t\t\t\t\t\t\n"<<endl;
    while(true) {
        cout<<"LIST OF ACTIONS:\n\n1. LIST ALL THE STATIONS IN THE MAP\n2. SHOW THE METRO MAP\n3. GET SHORTEST DISTANCE FROM A 'SOURCE' STATION TO A 'DESTINATION' STATION\n4. GET MINIMUM COST OF TRAVELLING FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n5. GET THE SHORTEST PATH FROM A 'SOURCE' STATION TO A 'DESTINATION' STATION\n6. GET THE PATH WITH THE MINIMUM COST TO TRAVEL FROM A 'SOURCE' STATION TO A 'DESTINATION' STATION\n7. EXIT\n\nNOTE: While entering the station name, don't enter the whole name. Instead just use the code. The codes can be found enclosed in parantheses with the station name.\n\n";
        int choice = -1;
        cout<<"Enter your choice from the menu: ";
        cin>>choice;
        if(choice==7) {
            cout<<"\n\nBYE! HAPPY JOURNEY\n\n"<<endl;
            break;
        }
        else if(choice==1) {
            cout<<endl<<endl;
            g.showStations();
            cout<<endl<<endl;
        }
        else if(choice==2) {
            cout<<endl<<endl;
            g.showMetroMap();
            cout<<endl<<endl;
        }
        else if(choice==4) {
            string src,dest;
            cout<<"Enter the SOURCE station code(starting point): ";
            cin>>src;
            cout<<"Enter the DESTINATION station code(ending point): ";
            cin>>dest;

            g.minimumCostDjikstra(src,dest);
        }
        else if(choice==3 || choice==5 || choice==6) {
            cout<<"\n\nYour requested feature is under development.\n\n"<<endl;
        }
        else {
            cout<<"\n\nInvalid input! Please try again\n\n"<<endl;
        }
    }
}

int main(){

    menu();
    return 0;
}