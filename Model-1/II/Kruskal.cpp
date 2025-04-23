#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class DisjointSet {
    public:
    int n;
    std::vector<int> arr;
    DisjointSet ( int n ) {
        this->n = n;
        arr.resize(n, 0);
        for ( int i = 0 ; i < n; i++ ) {
            arr[i] = i;
        }
    }
    int find( int u ) {
        if ( arr[u] != u ) {
            return find(arr[u]);
        }
        return u;
    }
    void Union( int u, int v ) {
        if ( find(u) != find(v) ) {
            arr[find(v)] = u;
        }
    }
};

class Edge {
    public:
    int source;
    int destination;
    int weight;
    Edge(int source, int destination, int weight) {
        this->source = source;
        this->destination = destination;
        this->weight = weight;
    }
};

class Graph {
    public:
    int nE;
    int nV;
    std::unordered_map<int, std::vector<Edge>> List;
    Graph( int nE, int nV ) {
        this->nE = nE;
        this->nV = nV;
        List.reserve(nV);
    }
    void inputGraph() {
        for ( int i = 0 ; i < nE; i++ ) {
            int u, v, w;
            std::cin >> u >> v >>w;
            List[u].emplace_back(u,v,w);
        }
    } 
    void Kruskal() {
        
        DisjointSet * set = new DisjointSet(nV);
        std::vector<Edge> Edges;
        for ( int i = 0; i < nV; i++ ) {
            for ( Edge e : List[i] ) {
                Edges.push_back(e);
            }
        }

        auto CustomComparator = [] ( const Edge &e1, const Edge &e2 ) {
           return e1.weight < e2.weight; 
        };

        std::sort(Edges.begin(), Edges.end(), CustomComparator);
        std::vector<Edge> res;
        int resWeight = 0;
        int i = 0, nTreeEdge = 0;
        while ( nTreeEdge < nV - 1 ) {
            Edge temp = Edges[i++];
            if ( set->find(temp.source) != set->find(temp.destination) ) {
                res.push_back(temp);
                nTreeEdge++;
                resWeight += temp.weight;
                set->Union(temp.source, temp.destination);
            }
        }
        for ( int i = 0; i < nV - 1; i++ ) {
            std::printf("Edge from %d to %d\n", res[i].source, res[i].destination);
        }
        std::printf("Total weight %d\n", resWeight);
    }
};

int main () {
    int nE, nV;
    std::cin >> nE >> nV;
    Graph * graph = new Graph(nE, nV);
    graph->inputGraph();
    graph->Kruskal();
    return 0;
}