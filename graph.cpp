// JAI BAJRANGBALI

#include<bits/stdc++.h>
using namespace std;

class Graph {
    private:
        unordered_map<int,vector<int>> vertices;

    public:
        void addVertex(int v) {
            vertices[v]=vector<int>();
        }

        void addEdge(int src, int dest) {
            //as travelling in both directions is possible, the graph is gonna be an undirected one
            vertices[src].push_back(dest);
            vertices[dest].push_back(src);
        }
};

int main(){

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
        else if(choice>=1 && choice<=6) {
            cout<<"\n\nYour requested feature is under development.\n\n"<<endl;
        }
        else {
            cout<<"\n\nInvalid input! Please try again\n\n"<<endl;
        }
    }
    return 0;
}