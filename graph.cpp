// JAI BAJRANGBALI

#include<bits/stdc++.h>
using namespace std;

class Graph {
    private:
        unordered_map<string,list<pair<string,int>>> verticesCost;
        unordered_map<string,list<pair<string,int>>> verticesDistance;
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

        void addVertexCost(string code) {
            string name = stationMapping[code];
            if(!name.empty()) {
                verticesCost[name] = list<pair<string,int>>();
            }
            else {
                cout<<"Invalid station code"<<endl;
            }
        }

        void addVertexDistance(string code) {
            string name = stationMapping[code];
            if(!name.empty()) {
                verticesDistance[name] = list<pair<string,int>>();
            }
            else {
                cout<<"Invalid station code"<<endl;
            }
        }

        void addEdgeCost(string code1, string code2, int weight) {
            //as travelling in both directions is possible, the graph is gonna be an undirected one
            string name1 = stationMapping[code1];
            string name2 = stationMapping[code2];

            if(!name1.empty() && !name2.empty()) {
                verticesCost[name1].push_back(make_pair(name2,weight));
                verticesCost[name2].push_back(make_pair(name1,weight));
            }
            else {
                cout<<"Invalid station code"<<endl;
            }
        }

        void addEdgeDistance(string code1, string code2, int weight) {
            //as travelling in both directions is possible, the graph is gonna be an undirected one
            string name1 = stationMapping[code1];
            string name2 = stationMapping[code2];

            if(!name1.empty() && !name2.empty()) {
                verticesDistance[name1].push_back(make_pair(name2,weight));
                verticesDistance[name2].push_back(make_pair(name1,weight));
            }
            else {
                cout<<"Invalid station code"<<endl;
            }
        }

        void showStations() {

            //either graph can be used to print all the stations
            for(auto station: verticesCost) {
                cout<<station.first<<endl;
            }
        }

        void showMetroMapCost() {

            cout<<"Following are the fares of travelling from source to destination"<<endl;
            for(auto station: verticesCost) {
                cout<<station.first<<"->";
                for(auto nbr: station.second) {
                    cout<<"("<<nbr.first<<", "<<nbr.second<<"), ";
                }
                cout<<endl;
            }
        }

        void showMetroMapDistance() {

            cout<<"\nFollowing are the distances from source to destination"<<endl;
            for(auto station: verticesDistance) {
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
            for(auto &i: verticesCost) {
                string node = i.first;
                stationIndices[node]=index++;
            }

            int n = verticesCost.size()+1;
            vector<int> dist(n,INT_MAX);
            set<pair<int,string>> s;

            dist[stationIndices[srcStation]]=0;
            s.insert(make_pair(0,srcStation));

            while(!s.empty()) {
                auto top = *(s.begin());
                int stationDist = top.first;
                string stationName = top.second;

                s.erase(s.begin());

                for(auto nbr: verticesCost[stationName]) {
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

        void minimumDistanceDjikstra(string srcCode,string destCode) {
            
            string srcStation = stationMapping[srcCode];
            string destStation = stationMapping[destCode];

            if(srcStation.empty() || destStation.empty()) {
                cout<<"\nEither source or destination code is invalid\n\n";
                return;
            }

            unordered_map<string,int> stationIndices;
            int index = 0;
            for(auto &i: verticesDistance) {
                string node = i.first;
                stationIndices[node]=index++;
            }

            int n = verticesDistance.size()+1;
            vector<int> dist(n,INT_MAX);
            set<pair<int,string>> s;

            dist[stationIndices[srcStation]]=0;
            s.insert(make_pair(0,srcStation));

            while(!s.empty()) {
                auto top = *(s.begin());
                int stationDist = top.first;
                string stationName = top.second;

                s.erase(s.begin());

                for(auto nbr: verticesDistance[stationName]) {
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
            cout<<"\nThe shortest distance from "<<srcStation<<" to "<<destStation<<" is "<<dist[stationIndices[destStation]]<<" KM.\n\n";
        }

        void shortestPathDistanceWise(string srcCode,string destCode) {

            string srcStation = stationMapping[srcCode];
            string destStation = stationMapping[destCode];

            queue<string> q;
            unordered_map<string,bool> visited;
            unordered_map<string,string> parent;

            q.push(srcStation);
            visited[srcStation]=true;
            parent[srcStation]="\0";

            while(!q.empty()) {
                string fNode = q.front();
                q.pop();
                for(auto nbr: verticesDistance[fNode]) {
                    if(!visited[nbr.first]) {
                        q.push(nbr.first);
                        visited[nbr.first]=true;
                        parent[nbr.first]=fNode;
                    }
                }
            }
            vector<string> ans;
            string node=destStation;
            while(node!="\0") {
                ans.push_back(node);
                node=parent[node];
            }

            cout<<endl<<"Printing distance wise shortest path between "<<srcStation<<" and "<<destStation<<endl<<endl;
            for(int i=ans.size()-1;i>=1;i--) cout<<ans[i]<<"->";
            cout<<ans[0]<<endl<<endl;
        }

        void minimumCostPath(string srcCode, string destCode) {

            string srcStation = stationMapping[srcCode];
            string destStation = stationMapping[destCode];

            queue<string> q;
            unordered_map<string,bool> visited;
            unordered_map<string,string> parent;

            q.push(srcStation);
            visited[srcStation]=true;
            parent[srcStation]="\0";

            while(!q.empty()) {
                string fNode = q.front();
                q.pop();
                for(auto nbr: verticesCost[fNode]) {
                    if(!visited[nbr.first]) {
                        q.push(nbr.first);
                        visited[nbr.first]=true;
                        parent[nbr.first]=fNode;
                    }
                }
            }
            vector<string> ans;
            string node=destStation;
            while(node!="\0") {
                ans.push_back(node);
                node=parent[node];
            }

            cout<<endl<<"Printing the path from "<<srcStation<<" to "<<destStation<<" which costs the least"<<endl<<endl;
            for(int i=ans.size()-1;i>=1;i--) cout<<ans[i]<<"->";
            cout<<ans[0]<<endl<<endl;
        }
};

void menu() {

    Graph gCost,gDistance;
    gCost.addVertexCost("GP");
    gCost.addVertexCost("KM");
    gCost.addVertexCost("LN");
    gCost.addVertexCost("NE");
    gCost.addVertexCost("IIT");
    gCost.addVertexCost("HK");
    gCost.addVertexCost("IGIT1");
    gCost.addVertexCost("HCC");

    gDistance.addVertexDistance("GP");
    gDistance.addVertexDistance("KM");
    gDistance.addVertexDistance("LN");
    gDistance.addVertexDistance("NE");
    gDistance.addVertexDistance("IIT");
    gDistance.addVertexDistance("HK");
    gDistance.addVertexDistance("IGIT1");
    gDistance.addVertexDistance("HCC");

    gCost.addEdgeCost("GP","KM",20);
    gCost.addEdgeCost("KM","LN",25);
    gCost.addEdgeCost("LN","NE",35);
    gCost.addEdgeCost("NE","IIT",40);
    gCost.addEdgeCost("IIT","HK",20);
    gCost.addEdgeCost("IIT","IGIT1",50);
    gCost.addEdgeCost("HK","HCC",45);

    gDistance.addEdgeDistance("GP","KM",2);
    gDistance.addEdgeDistance("KM","LN",2);
    gDistance.addEdgeDistance("LN","NE",3);
    gDistance.addEdgeDistance("NE","IIT",4);
    gDistance.addEdgeDistance("IIT","HK",2);
    gDistance.addEdgeDistance("IIT","IGIT1",5);
    gDistance.addEdgeDistance("HK","HCC",4);
    
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
            gCost.showStations();
            cout<<endl<<endl;
        }
        else if(choice==2) {
            cout<<endl<<endl;
            gCost.showMetroMapCost();
            gDistance.showMetroMapDistance();
            cout<<endl<<endl;
        }

        else if(choice==3) {
            string src,dest;
            cout<<"Enter the SOURCE station code(starting point): ";
            cin>>src;
            cout<<"Enter the DESTINATION station code(ending point): ";
            cin>>dest;

            gDistance.minimumDistanceDjikstra(src,dest);
        }

        else if(choice==4) {
            string src,dest;
            cout<<"Enter the SOURCE station code(starting point): ";
            cin>>src;
            cout<<"Enter the DESTINATION station code(ending point): ";
            cin>>dest;

            gCost.minimumCostDjikstra(src,dest);
        }

        else if(choice==5) {
            string src,dest;
            cout<<"Enter the SOURCE station code(starting point): ";
            cin>>src;
            cout<<"Enter the DESTINATION station code(ending point): ";
            cin>>dest;

            gDistance.shortestPathDistanceWise(src,dest);
        }

        else if(choice==6) {
            string src,dest;
            cout<<"Enter the SOURCE station code(starting point): ";
            cin>>src;
            cout<<"Enter the DESTINATION station code(ending point): ";
            cin>>dest;

            gCost.minimumCostPath(src,dest);
        }
        else {
            cout<<"\n\nInvalid input! Please try again\n\n"<<endl;
            break;
        }
    }
}

int main(){

    menu();
    return 0;
}