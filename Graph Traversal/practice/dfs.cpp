#include <iostream>
#include <stack>
#include <vector>
#include <queue>

using namespace std;
class Graph {
    public : 
    int nE;
    int nV;
    vector<int> Parent;
    vector<int> Distance;
    vector<int> Start;
    vector<int> Finish;
    vector<vector<int>> List;
    vector<bool> Visited;
    int time;
    Graph ( int nV, int nE ) {
        this->nE = nE;
        time = 0;
        this->nV = nV;
        Parent.resize(nV, -1);
        Distance.resize(nV, 2147483647);
        Start.resize(nV, 0);
        Finish.resize(nV, 0);
        List.resize(nV);
        Visited.resize(nV, false);
    } 
    // void runDFS() {
    //     // Distance[source] = 0;
    //     // Parent[source] = -1;
    //     for ( int i = 0; i < nV; i++ ) {
    //         if ( !Visited[i] ) {
    //             Distance[i] = 0;
    //             Parent[i] = -1;
    //             DFS(i);
    //         }
    //     }
    //     // DFS(source);
    // } 
    // void DFS (int vertex) {
    //     Visited[vertex] = true; 
    //     for( int v : List[vertex] ) {
    //         if (!Visited[v] ) {
    //             Parent[v] = vertex;
    //             Distance[v] = 1 + Distance[vertex];
    //             DFS(v);
    //         }
    //     }
    // } 


    void runDFS() {
        for ( int i = 0 ; i < nV; i++ ) {
            if ( !Visited[i] ) {
                Parent[i] = -1;
                Distance[i] = 0;
                DFS(i);
            } 
        }
    }

    void DFS(int vertex) {
        Visited[vertex] = true;
        Start[vertex] = time++;
        for ( int v : List[vertex] ) {
            if ( Visited[v] == false ) {
                Parent[v] = vertex;
                Distance[v] =  1 + Distance[vertex];
                DFS(v);
            }
        }
        Finish[vertex] = time++;
    }
    
    void printDetails() {
        for ( int i = 0; i < nV; i++ ) {
            cout << "Vertex " << i + 1 << "\n";
            cout << "Parent : " << Parent[i] + 1 << "\n";
            cout << "Start : " << Start[i] << " Finish time : " << Finish[i] << " \n";
            cout << "Distance : " << Distance[i] << "\n\n";

        }
    }
};

int main () {
    Graph * graph = new Graph(5,7);
    graph->List = {
        {1,2}, {3,4}, {1,4}, {4}, {}
    };
    graph->runDFS();
    graph->printDetails();
}
