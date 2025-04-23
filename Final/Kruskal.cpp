#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include <algorithm>

class DisjointSet {
    public:
    int n;
    std::vector<int> arr;
    DisjointSet(int n) {
        this->n = n;
        arr.resize(n);
        for ( int i = 0 ; i < n; i++ ) {
            arr[i] = i;
        }
    }
    int find(int u) {
        if ( arr[u] != u ) arr[u] = find(arr[u]);
        return arr[u];
    }
    void Union(int u, int v) {
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
    Edge(int source, int destination, int weight ) {
        this->source = source;
        this->destination = destination;
        this->weight = weight;   
    }
};
class  Graph {
    public:
    int nE;
    int nV;
    std::vector<Edge> List;
    Graph(int nE, int nV) {
        this->nE = nE;
        this->nV = nV;
    }
    void inputGraph() {
        for ( int i = 0 ; i < nE; i+= 1 ) {
            int u, v, w;
            std::cin >> u >> v >> w;
            List.emplace_back(u,v,w);
        } 
    }
    void kruskal(){
        DisjointSet * set = new DisjointSet(nV);
        auto CustomComparator = []( const Edge &e1, const Edge &e2 ) {
            return e1.weight < e2.weight;
        };
        std::sort(List.begin(), List.end(), CustomComparator);
        int nTreeEdgees = 0, i = 0, resWeight = 0;
        std::vector<Edge> res;
        while ( nTreeEdgees < nV - 1 ) {
            Edge temp = List[i++];
            if ( set->find(temp.source) != set->find(temp.destination) ) {
                res.push_back(temp);
                nTreeEdgees+= 1;
                resWeight += temp.weight;
                set->Union(temp.source, temp.destination);
            }
        }        

        for ( int i = 0 ; i < nV - 1; i++ ) {
            std::printf("Edge from %d to %d \n", res[i].source, res[i].destination);
        }
        std::printf("total cost = %d", resWeight);
    }
};


int main () {
    int nE, nV;
    std::cin >> nE >> nV;
    Graph * graph = new Graph(nE, nV);
    graph->inputGraph();
    graph->kruskal();
    return 0;
}