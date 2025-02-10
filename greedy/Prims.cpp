#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <bits/stdc++.h>

class Edge {
    public:
        int source;
        int destination;
        int weight;
        Edge(int source,int destination, int weight) {
            this->destination = destination;
            this->weight = weight;
            this->source = source;
        }
};
class Graph {
    public:
    int nE, nV;
    std::unordered_map<int, std::vector<Edge>> List;
    Graph ( int nE, int nV ) {
        this->nE = nE;
        this->nV = nV;
        List.reserve(nV);
    }
    void inputGraph() {
        int inputs = 0;
            std::cout << "Enter the edges in this format vertex 1 vertex 2 weight \n";
        while ( inputs < nE ) {
            int v1, v2, w;
            std::cin >> v1 >> v2 >> w;
            if ( v1 <= nV && v2 <= nV ){
                List[v1].emplace_back(v1, v2, w);
                List[v2].emplace_back(v2, v1, w);
                inputs++;
            } else {
                std::cout << "NOt a valid edge \n"; 
            }
       }
    }
    void Prims () {
       int source = 1;
       int resWeight = 0;
        std::vector<Edge> treeEdges;
        std::vector<int> Visited(nV + 1, 0);
        auto customComparator = []( const Edge &e1, const Edge &e2 ) {
         return e1.weight > e2.weight;
        };
        std::priority_queue<Edge, std::vector<Edge>, decltype(customComparator)> pq(customComparator);
        Visited[source] = 1;
        for ( Edge e : List[source] ) {
            pq.push(e);
        } 
       
       while ( treeEdges.size() != nV - 1 ) {
        Edge e1 = pq.top();
        pq.pop();
        if ( Visited[e1.destination] ) continue;
        treeEdges.push_back(e1);
        Visited[e1.destination] = 1;
        resWeight += e1.weight;
        for ( Edge e : List[e1.destination] ) {
            if ( !Visited[e.destination] ) {
                pq.push(e);
            }
        }
       }
       for ( Edge i : treeEdges ) 
        {
            std::cout << "Edge : source : " << i.source << " Destination :  " << i.destination << " weight  : " << i.weight << std::endl; 
        }
        std::cout << "Cost of Tree : " << resWeight << std::endl;
    }
};

int main () {
    Graph * graph = new Graph(14, 9); 
    graph->inputGraph();
    graph->Prims();
}