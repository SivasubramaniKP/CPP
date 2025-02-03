#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

class DisjointSet {
    public:
    std::vector<int> Parent;
    int nodes;
    DisjointSet(int nodes) {
        this->nodes = nodes;
        Parent.resize(nodes);
        for ( int i = 0 ; i < nodes; i++ ) {
            Parent[i] = i;
        }
    }
    int find( int u ) {
        if ( Parent[u] != u ) {
            find(Parent[u]);
        } else {
            return u;
        }
    }   
    void Union ( int u, int v ) {
        if ( find(u) != find(v) ) {
            Parent[find(v)] = u;
        }
    }
    void printParentArray() {
        for ( int i : Parent ) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
};

class Edge {
    public:
        int destination;
        int weight;
        Edge(int destionation, int weight) {
            this->destination = destination;
            this->weight = weight;
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
                List[v1].push_back(Edge(v2, w));
                List[v2].push_back(Edge(v1, w));
                inputs++;
            } else {
                std::cout << "NOt a valid edge \n"; 
            }
       }
    }
};