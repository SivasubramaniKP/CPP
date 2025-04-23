#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
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

     Graph(int nE, int nV) {
        this->nE = nE;
        this->nV = nV;
        List.reserve(nV);
    }

    void inputgraph() {
        for ( int i = 0 ; i < nE; i++ ) {
            int u,v,w;
            std::cin >> u >> v >> w;
            List[u].push_back(Edge(u,v,w));
        }
    }

    void Dijkstra(int source) { 
        std::vector<int> Dist(nV, INT_MAX);
        auto customComparator = [](const std::pair<int, int> &a, const std::pair<int,int> &b){
            return a.first > b.first;
        };
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int, int>>, decltype(customComparator)> PQ(customComparator);
        Dist[source] = 0;
        PQ.push({0, source});

        while ( !PQ.empty() ) {
            int u = PQ.top().first;
            int d = PQ.top().second;
            PQ.pop();
            if ( d > Dist[u] ) continue;;

            for ( Edge e : List[u] ) {
                int v = e.destination;
                int w = e.weight;
                if ( Dist[v] > Dist[u] + w ) {
                    Dist[v] = Dist[u] + w;
                    PQ.push({v, Dist[v]});
                }
            }
        }
        for ( int i = 0 ; i < nV; i++ ) {
            std::cout << "Vertex :"  << ( i  ) << " Shortest path from source : " << Dist[i] << std::endl;
        }
    }
};
int main() {
    Graph * graph = new Graph(14,9);
    graph->inputgraph();
    graph->Dijkstra(0);
    return 0;
}

