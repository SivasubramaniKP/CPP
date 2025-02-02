#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
class Edge {
    public:
    int destination;
    int weight;
    Edge(int dest, int w) : destination(dest), weight(w) {};
    
};

class Graph {
    public:
    int nE; int nV;
    std::unordered_map<int, std::vector<Edge>> List;

    Graph(int nV, int nE) {
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

    void printGraph() {
        for ( int i = 1 ; i <= nV; i++ ) {
            for ( Edge e : List[i] ) {
                std::cout << i << " -> " << e.destination << std::endl;
                std::cout << "Weight : " << e.weight << std::endl;
            }
            std::cout << std::endl;
        }
    }

    struct CustomComparator{
        bool operator() (const std::pair<int,int> &a, const std::pair<int,int> &b) {
            if ( a.first < b.first ) return true;
            return false;
        }
    };

    void Dijkstra( int source )  {
        std::vector<int> dist(nV + 1, INT_MAX);
        dist[source] = 0;
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, CustomComparator> PQ;
        PQ.push({0, source});

        while ( !PQ.empty() ) {
            int u = PQ.top().second;
            int d = PQ.top().first;
            PQ.pop();

            if ( d > dist[u] ) continue;

            for ( Edge neighbour : List[u] ) {
                int v = neighbour.destination;
                int w = neighbour.weight;
                if ( dist[u] + w < dist[v] ) {
                    dist[v] = dist[u] + w;
                    PQ.push({dist[v], v});
                }
            } 
        }

        for ( int i = 1 ; i <= nV; i++ ) {
            std::cout << "distance from " << source << " to " << i << " " << dist[i] << "\n";
        }
    } 

};

int main () {
    Graph * graph = new Graph(5, 7);
    graph->inputGraph();
    graph->printGraph();
    graph->Dijkstra(1);
    return 0;
}