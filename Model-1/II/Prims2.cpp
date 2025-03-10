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

    void Prims () {
        std::vector<Edge> res;
        int resWeight = 0, TreeEdges = 0;
        auto CustomComparator = [] ( const Edge &e1, const Edge &e2 ) {
            return e1.weight > e2.weight;
        };
        int SOURCE = 0;
        std::priority_queue<Edge, std::vector<Edge>, decltype(CustomComparator)> PQ(CustomComparator);
        for ( Edge e : List[SOURCE] ) {
            PQ.push(e);
        }
        std::vector<int> Visited(nV, 0);
        Visited[SOURCE] = 1; 
        while ( TreeEdges < nV - 1 ) {
            Edge temp = PQ.top(); PQ.pop();
            if( Visited[temp.destination] ) continue;
            res.push_back(temp);
            resWeight += temp.weight;
            TreeEdges ++;
            Visited[temp.destination] = 1;
            for ( Edge e : List[temp.destination] ) {
                if ( !Visited[e.destination] ) {
                    PQ.push(e);
                }
            }
        }
        for ( int i = 0 ; i < res.size(); i++ ) {
            std::printf("Edge from %d to %d\n", res[i].source, res[i].destination);
        }
        std::printf("Total Cost : %d", resWeight);
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
