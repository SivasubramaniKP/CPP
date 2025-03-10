#include <iostream>
#include <climits> 
#include <vector>
#include <unordered_map>
#include <queue>
class Edge {
    public:
    int source;
    int destination;
    int weight;
    Edge ( int source, int destination, int weight ) {
        this->source = source;
        this->destination = destination;
        this->weight = weight;    
    }  
};

class Graph{

    public:
    int nE;
    int nV;
    std::unordered_map<int, std::vector<Edge>> List;

    Graph(int nE, int nV) {
        this->nE = nE;
        this->nV = nV;
        List.reserve(nV);
    }

    void addEdge(int u, int v, int w) {
        List[u].emplace_back(Edge(u,v,w));
    }
    void inputGraph() {
        for ( int i = 0 ; i  < nE; i++ ) {
            int u, v, w;
            std::cin >> u >> v >> w;
            addEdge(u,v,w);
        }
    }
    void Dijkstra(int source) {
        std::vector<int> Dist(nV, INT_MAX);
        Dist[source] = 0;
        auto CustomComparator = [] ( const std::pair<int,int> &a, const std::pair<int,int> &b ) {
            return a.first > b.first;
        };
        // std::printf("")
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, decltype(CustomComparator)> PQ(CustomComparator);
        PQ.push({0, source});
        while ( !PQ.empty() ) {
            int u = PQ.top().second;
            int d = PQ.top().first;
            PQ.pop();
            if ( d > Dist[u] ) continue;
            for ( Edge e : List[u] ) {
                int v = e.destination;
                int w = e.weight;
                if ( Dist[v] > Dist[u] + w ) {
                    Dist[v] = Dist[u] + w;
                    PQ.push({Dist[v], v});
                }
            }
        } 
        for ( int i = 0 ; i < nV; i++ ) {
            std::printf("%d ", Dist[i]);
        }
    }
};  

int main () {
    // std::printf("Hello world");
    int nE, nV;
    std::cin >> nE >> nV;
    Graph *graph = new Graph(nE, nV);
    graph->inputGraph();
    graph->Dijkstra(0);
    return 0;
}