// JAI BAJRANGBALI

#include<bits/stdc++.h>
using namespace std;

class Graph {
    private:
        unordered_map<string,vector<string>> vertices;

    public:
        void addVertex(string v) {
            vertices[v]=vector<string>();
        }

        void addEdge(string src, string dest) {
            //as travelling in both directions is possible, the graph is gonna be an undirected one
            vertices[src].push_back(dest);
            vertices[dest].push_back(src);
        }

        void showStations() {
            for(auto station: vertices) {
                cout<<station.first<<endl;
            }
        }

        void showMetroMap() {
            for(auto station: vertices) {
                cout<<station.first<<"->";
                for(auto neighbour: station.second) cout<<neighbour<<", ";
                cout<<endl;
            }
        }
};

void menu() {

    Graph g;
    g.addVertex("Govindpuri");
    g.addVertex("Kalkaji Mandir");
    g.addVertex("Lajpat Nagar");
    g.addVertex("Nehru Enclave");
    g.addVertex("IIT");
    g.addVertex("Hauz Khas");
    g.addVertex("IGI Terminal 1");
    g.addVertex("Huda City Center");

    g.addEdge("Govindpuri","Kalkaji Mandir");
    g.addEdge("Kalkaji Mandir","Lajpat Nagar");
    g.addEdge("Lajpat Nagar","Nehru Enclave");
    g.addEdge("Nehru Enclave","IIT");
    g.addEdge("IIT","Hauz Khas");
    g.addEdge("IIT","IGI Terminal 1");
    g.addEdge("Hauz Khas","Huda City Center");
    
    cout<<"\n\t\t\t\t\t\tWELCOME TO METRO APP\t\t\t\t\t\t\n"<<endl;
    while(true) {
        cout<<"LIST OF ACTIONS:\n\n1. LIST ALL THE STATIONS IN THE MAP\n2. SHOW THE METRO MAP\n3. GET SHORTEST DISTANCE FROM A 'SOURCE' STATION TO A 'DESTINATION' STATION\n4. GET MINIMUM COST OF TRAVELLING FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n5. GET THE SHORTEST PATH FROM A 'SOURCE' STATION TO A 'DESTINATION' STATION\n6. GET THE PATH WITH THE MINIMUM COST TO TRAVEL FROM A 'SOURCE' STATION TO A 'DESTINATION' STATION\n7. EXIT\n\n";
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
        else if(choice>=3 && choice<=6) {
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