// JAI BAJRANGBALI

#include<iostream>
#include<unordered_map>
#include<set>
#include<vector>
#include<list>
#include<limits.h>
#include<queue>

using namespace std;

class Graph {
    private:
        unordered_map<string,list<pair<string,int>>> verticesCost;
        unordered_map<string,list<pair<string,int>>> verticesDistance;
        unordered_map<string,string> stationMapping;

    public:

        Graph() {
            stationMapping = {
                {"KM","Kalkaji Mandir(KM)"},
                {"NE","Nehru Enclave(NE)"},
                {"CD","Chirag Delhi(CD)"},
                {"GK1","Greater Kailash 1(GK1)"},
                {"HK","Hauz Khas(HK)"},
                {"MN","Malviya Nagar(MN)"},
                {"SK","Saket(SK)"},
                {"SKP","Sikanderpur(SKP)"},
                {"MGR","MG Road(MGR)"},
                {"HCC","Huda City Center(HCC)"},
                {"CHP","Chhatarpur(CHP)"},
                {"QM","Qutub Minar(QM)"},
                {"RG","Rajouri Garden(RG)"},
                {"KE","Kohat Enclave(KE)"},
                {"AN","Adarsh Nagar(AN)"},
                {"SB","Samaypur Badli(SB)"},
                {"R14","Rohini Sector 14(R14)"},
                {"CC","Chandni Chowk(CC)"},
                {"ND","New Delhi(ND)"},
                {"RC","Rajiv Chowk(RC)"},
                {"KB","Karol Bagh(KB)"},
                {"MH","Mandi House(MH)"},
                {"NP","Nehru Place(NP)"},
                {"JP","Janakpuri(JP)"},
                {"PM","Palam(PM)"},
                {"IGIT1","IGI Terminal 1(IGIT1)"},
                {"IIT","IIT(IIT)"}
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

            cout<<"Following are the fares of travelling from source to destination\n\n";
            for(auto station: verticesCost) {
                cout<<station.first<<"->";
                for(auto nbr: station.second) {
                    cout<<"("<<nbr.first<<", "<<nbr.second<<"), ";
                }
                cout<<endl;
            }
        }

        void showMetroMapDistance() {

            cout<<"\nFollowing are the distances from source to destination\n\n";
            for(auto station: verticesDistance) {
                cout<<station.first<<"->";
                for(auto nbr: station.second) {
                    cout<<"("<<nbr.first<<", "<<nbr.second<<"), ";
                }
                cout<<endl;
            }
        }

        void minimumCostDjikstra(string srcCode,string destCode) {\
        

            if(srcCode==destCode) {
                cout<<"\nSource and Destination cannot be same\n\n";
                return;
            }
            
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

            if(srcCode==destCode) {
                cout<<"\nSource and Destination cannot be same\n\n";
                return;
            }
            
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

            if(srcCode==destCode) {
                cout<<"\nSource and Destination cannot be the same\n\n";
                return;
            }

            string srcStation = stationMapping[srcCode];
            string destStation = stationMapping[destCode];

            if(srcStation.empty() || destStation.empty()) {
                cout<<"\nEither source or destination code is invalid\n\n";
                return;
            }

            priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
            unordered_map<string, bool> visited;
            unordered_map<string, int> cost;
            unordered_map<string, string> parent;

            pq.push(make_pair(0,srcStation));
            visited[srcStation] = true;
            cost[srcStation] = 0;
            parent[srcStation] = "";

            while(!pq.empty()) {
                auto top = pq.top();
                pq.pop();

                int stationCost = top.first;
                string stationName = top.second;

                if(stationName==destStation) break;

                if(stationCost>cost[stationName]) continue;

                for(auto nbr: verticesDistance[stationName]) {
                    string nbrStation = nbr.first;
                    int nbrCost = nbr.second;

                    int newCost = stationCost + nbrCost;

                    if(!visited[nbrStation] || newCost<cost[nbrStation]) {
                        visited[nbrStation] = true;
                        cost[nbrStation] = newCost;
                        parent[nbrStation] = stationName;
                        pq.push(make_pair(cost[nbrStation],nbrStation));
                    }
                }
            }

            if(!visited[destStation]) {
                cout<<"\nNo path exists between "<<srcStation<<" and "<< destStation<< "\n\n";
                return;
            }

            vector<string> path;
            string node = destStation;
            while(node != "") {
                path.push_back(node);
                node = parent[node];
            }

            cout << "\nPrinting distance wise shortest path between " <<srcStation<< " to " <<destStation<<":\n\n";
            for(int i=path.size()-1; i>=1;i--) cout<<path[i]<<" -> ";
            cout<<path.front()<<"\n\n";
        }

        void minimumCostPath(string srcCode, string destCode) {
            
            if(srcCode==destCode) {
                cout<<"\nSource and Destination cannot be the same\n\n";
                return;
            }

            string srcStation = stationMapping[srcCode];
            string destStation = stationMapping[destCode];

            if(srcStation.empty() || destStation.empty()) {
                cout<<"\nEither source or destination code is invalid\n\n";
                return;
            }

            priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
            unordered_map<string, bool> visited;
            unordered_map<string, int> cost;
            unordered_map<string, string> parent;

            pq.push(make_pair(0,srcStation));
            visited[srcStation] = true;
            cost[srcStation] = 0;
            parent[srcStation] = "";

            while(!pq.empty()) {
                auto top = pq.top();
                pq.pop();

                int stationCost = top.first;
                string stationName = top.second;

                if(stationName==destStation) break;

                if(stationCost>cost[stationName]) continue;

                for(auto nbr: verticesCost[stationName]) {
                    string nbrStation = nbr.first;
                    int nbrCost = nbr.second;

                    int newCost = stationCost + nbrCost;

                    if(!visited[nbrStation] || newCost<cost[nbrStation]) {
                        visited[nbrStation] = true;
                        cost[nbrStation] = newCost;
                        parent[nbrStation] = stationName;
                        pq.push(make_pair(cost[nbrStation],nbrStation));
                    }
                }
            }

            if(!visited[destStation]) {
                cout<<"\nNo path exists between "<<srcStation<<" and "<< destStation<< "\n\n";
                return;
            }

            vector<string> path;
            string node = destStation;
            while(node != "") {
                path.push_back(node);
                node = parent[node];
            }

            cout << "\nPrinting the path from " <<srcStation<< " to " <<destStation<< " which costs the least:\n\n";
            for(int i=path.size()-1; i>=1;i--) cout<<path[i]<<" -> ";
            cout<<path.front()<<"\n\n";
        }
};

void menu() {

    Graph gCost,gDistance;

    //ADDING STATIONS TO THE FARE GRAPH
    gCost.addVertexCost("KM");
    gCost.addVertexCost("NE");
    gCost.addVertexCost("CD");
    gCost.addVertexCost("GK1");
    gCost.addVertexCost("HK");
    gCost.addVertexCost("MN");
    gCost.addVertexCost("SK");
    gCost.addVertexCost("SKP");
    gCost.addVertexCost("MGR");
    gCost.addVertexCost("HCC");
    gCost.addVertexCost("CHP");
    gCost.addVertexCost("QM");
    gCost.addVertexCost("RG");
    gCost.addVertexCost("KE");
    gCost.addVertexCost("AN");
    gCost.addVertexCost("SB");
    gCost.addVertexCost("R14");
    gCost.addVertexCost("CC");
    gCost.addVertexCost("ND");
    gCost.addVertexCost("RC");
    gCost.addVertexCost("KB");
    gCost.addVertexCost("MH");
    gCost.addVertexCost("NP");
    gCost.addVertexCost("JP");
    gCost.addVertexCost("PM");
    gCost.addVertexCost("IGIT1");
    gCost.addVertexCost("IIT");

    //ADDING FARES TO THE FARE GRAPH
    gCost.addEdgeCost("KM","NE",8);
    gCost.addEdgeCost("NE","CD",10);
    gCost.addEdgeCost("CD","GK1",12);
    gCost.addEdgeCost("HK","GK1",14);
    gCost.addEdgeCost("HK","MN",10);
    gCost.addEdgeCost("HK","IIT",8);
    gCost.addEdgeCost("SK","MN",7);
    gCost.addEdgeCost("SK","SKP",9);
    gCost.addEdgeCost("MGR","SKP",6);
    gCost.addEdgeCost("MGR","HCC",10);
    gCost.addEdgeCost("MGR","CHP",11);
    gCost.addEdgeCost("QM","CHP",6);
    gCost.addEdgeCost("QM","IIT",50);
    gCost.addEdgeCost("QM","RG",8);
    gCost.addEdgeCost("KE","RG",6);
    gCost.addEdgeCost("KE","AN",11);
    gCost.addEdgeCost("SB","AN",12);
    gCost.addEdgeCost("SB","R14",5);
    gCost.addEdgeCost("CC","R14",3);
    gCost.addEdgeCost("CC","ND",12);
    gCost.addEdgeCost("RC","ND",16);
    gCost.addEdgeCost("RC","KB",7);
    gCost.addEdgeCost("RC","MH",8);
    gCost.addEdgeCost("NP","MH",4);
    gCost.addEdgeCost("NP","KM",6);
    gCost.addEdgeCost("IIT","IGIT1",18);
    gCost.addEdgeCost("PM","IGIT1",20);
    gCost.addEdgeCost("PM","JP",13);

    //ADDING STATIONS TO THE DISTANCE GRAPH
    gDistance.addVertexDistance("KM");
    gDistance.addVertexDistance("NE");
    gDistance.addVertexDistance("CD");
    gDistance.addVertexDistance("GK1");
    gDistance.addVertexDistance("HK");
    gDistance.addVertexDistance("MN");
    gDistance.addVertexDistance("SK");
    gDistance.addVertexDistance("SKP");
    gDistance.addVertexDistance("MGR");
    gDistance.addVertexDistance("HCC");
    gDistance.addVertexDistance("CHP");
    gDistance.addVertexDistance("QM");
    gDistance.addVertexDistance("RG");
    gDistance.addVertexDistance("KE");
    gDistance.addVertexDistance("AN");
    gDistance.addVertexDistance("SB");
    gDistance.addVertexDistance("R14");
    gDistance.addVertexDistance("CC");
    gDistance.addVertexDistance("ND");
    gDistance.addVertexDistance("RC");
    gDistance.addVertexDistance("KB");
    gDistance.addVertexDistance("MH");
    gDistance.addVertexDistance("NP");
    gDistance.addVertexDistance("JP");
    gDistance.addVertexDistance("PM");
    gDistance.addVertexDistance("IGIT1");
    gDistance.addVertexDistance("IIT");

    //ADDING DISTANCES TO THE DISTANCE GRAPH
    gDistance.addEdgeDistance("KM","NE",8);
    gDistance.addEdgeDistance("NE","CD",10);
    gDistance.addEdgeDistance("CD","GK1",12);
    gDistance.addEdgeDistance("HK","GK1",14);
    gDistance.addEdgeDistance("HK","MN",10);
    gDistance.addEdgeDistance("HK","IIT",8);
    gDistance.addEdgeDistance("SK","MN",7);
    gDistance.addEdgeDistance("SK","SKP",9);
    gDistance.addEdgeDistance("MGR","SKP",6);
    gDistance.addEdgeDistance("MGR","HCC",10);
    gDistance.addEdgeDistance("MGR","CHP",11);
    gDistance.addEdgeDistance("QM","CHP",6);
    gDistance.addEdgeDistance("QM","IIT",50);
    gDistance.addEdgeDistance("QM","RG",8);
    gDistance.addEdgeDistance("KE","RG",6);
    gDistance.addEdgeDistance("KE","AN",11);
    gDistance.addEdgeDistance("SB","AN",12);
    gDistance.addEdgeDistance("SB","R14",5);
    gDistance.addEdgeDistance("CC","R14",3);
    gDistance.addEdgeDistance("CC","ND",12);
    gDistance.addEdgeDistance("RC","ND",16);
    gDistance.addEdgeDistance("RC","KB",7);
    gDistance.addEdgeDistance("RC","MH",8);
    gDistance.addEdgeDistance("NP","MH",4);
    gDistance.addEdgeDistance("NP","KM",6);
    gDistance.addEdgeDistance("IIT","IGIT1",18);
    gDistance.addEdgeDistance("PM","IGIT1",20);
    gDistance.addEdgeDistance("PM","JP",13);

    
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
            return;
        }
    }
}

int main(){

    menu();
    return 0;
}