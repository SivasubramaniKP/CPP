#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <vector>
#include <climits>
class Edge {
    public:
        int source;
        int destination;
        int weight;
    Edge( int source, int destination, int weight ) {
        this->weight = weight;
        this->source = source;
        this->destination = destination;
    }
};

class Graph {
    public:
        int nE;
        int nV;
        std::unordered_map<int,std::vector<Edge>> List;
    Graph ( int nE, int nV ) {
        this->nE = nE;
        this->nV = nV;
        List.reserve(nV);
    }
    void addEdge( int u, int v, int e ) {
        List[u].emplace_back(Edge(u,v,e));
    }
    void inputGraph() {
        for ( int i = 0 ; i  < nE; i++ ) {
            int u, v, e;
            std::cin >> u >> v >> e;
            addEdge(u,v, e);
        }
    }
    void Dijkstra( int source ) {

        std::vector<int> Dist(nV, INT_MAX);
        auto CustomComparator = [] ( const std::pair<int, int> &a, const std::pair<int, int> &b ) {
            return a.first > b.first;
        };
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, decltype(CustomComparator)> PQ(CustomComparator);
        Dist[source] = 0;
        PQ.push({0, source});

        while ( !PQ.empty() ) {
            int u = PQ.top().second;
            int d = PQ.top().first;
            PQ.pop();
            if ( d > Dist[u] ) continue;
            for ( Edge e : List[u] ) {
                int v = e.destination;
                int w = e.weight;
                if ( Dist[v] > w + Dist[u] ) {
                    Dist[v] = w + Dist[u];
                    PQ.push({Dist[v], v});
                }
            }

        } 
        for ( int i = 0 ; i  < nV; i++ ) {
            std::cout << "Vertex " << i + 1 << " Shortest path from the node is " << Dist[i] << "\n";
        }
    }

};

int main () {
    int nE, nV;
    std::cin >> nE >> nV;
    Graph * graph = new Graph(nE, nV);
    graph->inputGraph();
    graph->Dijkstra(0);
    return 0;
}
