#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

class Edge {
    public:
    int source;
    int destinaton;
    int weight;
    Edge(int source, int destination, int weight) {
        this->destinaton = destination;
        this->weight = weight;
        this->source = source;
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

    void inputgraph() {
        std::cout << "Enter the edges in this format source destination weight\n";
        for ( int i = 0 ; i < nE; i++ ) {
            int u,v,w;
            std::cin >> u >> v >> w;
            List[u].push_back(Edge(u,v,w));
        }
    }

    // void Dijkstra(int source) {
    //    std::vector<int> dist(nV, INT32_MAX);
    //    dist[source] = 0;
    //    auto CustomComparator = []( const std::pair<int,int> &a, const std::pair<int,int> &b ) {
    //     return a.first > b.first;
    //    };
    //    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(CustomComparator)> PQ(CustomComparator); 
    //    PQ.push({0, source});


    //    while ( !PQ.empty() ) {
    //     int u = PQ.top().second;
    //     int d = PQ.top().first;
    //     PQ.pop();
    //     if ( d > dist[u] ) continue;
        
    //     for ( Edge e : List[u] ) {
    //         int v = e.destinaton;
    //         int w = e.weight;
    //         if ( dist[v] > dist[u] + w ) {
    //             dist[v] = dist[u] + w;
    //             PQ.push({dist[v], v});
    //         }
    //     } 
    //    }

    //    for ( int i : dist ) {
    //     std::cout << i << " ";
    //    }
    // }


    void Dijkstra(int source) {
        std::vector<int> dist(nV, INT32_MAX);
        auto CustomComparator = [](const std::pair<int,int> &a, const std::pair<int,int> &b) {
            return a.first > b.first;
        };
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, decltype(CustomComparator)> PQ(CustomComparator);

        dist[source] = 0;
        PQ.push({0, source});

        while ( !PQ.empty() ) {
            int u = PQ.top().second;
            int d = PQ.top().first;
            PQ.pop();

            if ( d > dist[u] ) continue;

            for ( Edge e : List[u] ) {
                int v = e.destinaton;
                int w = e.weight;
                if ( dist[v] > dist[u] + w ) {
                    dist[v] = dist[u] + w;
                    PQ.push({dist[v], v});
                }
            }
        } 
        for ( int i = 0 ; i < nV; i++ ) {
            std::cout << "Vertex :"  << ( i + 1) << " Shortest path from source : " << dist[i] << std::endl;
        }

    }
};

int main() {
    Graph * graph = new Graph(14,9);
    graph->inputgraph();
    graph->Dijkstra(0);

    return 0;
}
