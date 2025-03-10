#include <iostream>
#include <vector>
#include <algorithm>

class DisjointSet {

    public:
    int n;
    std::vector<int> arr;
    DisjointSet(int n) 
    {
        this->n = n;
        arr.resize(n);
        for ( int i = 0 ; i < n; i++ ) {
            arr[i] = i;
        }
    }
        int find( int u ) {
            if ( arr[u] != u ) return find(arr[u]);
            return arr[u];
        }
        void Union( int u , int v ) {
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

class Graph{
    public:
    int nE;
    int nV;
    std::vector<Edge> List;
    Graph( int nE, int nV ) {
        this->nE = nE;
        this->nV = nV;
        List.reserve(nV);
    }
    void inputGraph() {
        for ( int i = 0 ; i < nE; i++ ) {
            int u, v, w;
            std::cin >> u >> v >>w;
            List.emplace_back(u,v,w);
        }
    }
    void Kruskal() {
        DisjointSet * set = new DisjointSet(nV);
        auto CustomComparator = [] ( const Edge &e1, const Edge &e2 ) {
            return e1.weight < e2.weight;
        };
        std::sort(List.begin(), List.end(), CustomComparator);
        int nTreeEdges = 0, i = 0, resWeight = 0;
        std::vector<Edge> res;
        while ( nTreeEdges < nV - 1 ) {
            Edge temp = List[i++];
            if ( set->find(temp.source) != set->find(temp.destination) ) {
                res.push_back(temp);
                nTreeEdges += 1;
                resWeight += temp.weight;
                set->Union(temp.source, temp.destination);
            }
        }  

        for ( int i = 0 ; i < res.size(); i++ ) {
            std::printf("Edge from %d to %d \n", res[i].source, res[i].destination);
        }
        std::printf("total weight : %d", resWeight);
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