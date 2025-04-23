#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
class Edge {
    public:
    int source;
    int destination;
    int weight;
    Edge( int source, int destination, int weight ) {
        this->source = source;
        this->weight = weight;
        this->destination = destination;
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
            std::cin >> u >> v >> w;
            List[u].emplace_back(u,v,w);
            List[v].emplace_back(v,u,w);
        }
    }
    void Prims() {
        int SOURCE = 0;
        std::vector<Edge> res;
        std::vector<int> Visited(nV, 0);
        Visited[SOURCE] = 1;
        auto CustomComparator = []( const Edge &e1, const Edge &e2 ) {
            return e1.weight > e2.weight;
        };

        std::priority_queue<Edge, std::vector<Edge>, decltype(CustomComparator)> PQ(CustomComparator);
        for ( Edge e : List[SOURCE] ) PQ.push(e);
        int TreeEdge = 0, resWeight = 0;
        while ( TreeEdge < nV - 1 ) {
            Edge e1 = PQ.top();
            PQ.pop();
            if ( Visited[e1.destination] ) continue;;
            res.push_back(e1);
            resWeight += e1.weight;
            Visited[e1.destination] = 1;
            for ( Edge e : List[e1.destination] ) {
                if ( !Visited[e.destination] ) {
                    PQ.push(e);
                }
            }
            TreeEdge += 1;
        }
        std::cout << "Cost : " << resWeight; 
    }
};


int main () {
     int nE, nV;
     std::cin >> nE >> nV;
     std::cout << nE << nV;
     Graph * graph = new Graph(nE, nV);
     graph->inputGraph();
     graph->Prims();
     return 0;
}
