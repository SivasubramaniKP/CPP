#include <iostream>
#include <vector>
#include <climits>
#include <queue>
class Graph {
    public:
    int nE;
    int nV;
    std::vector<std::vector<int>> Matrix;

    Graph( int nV) {
        
        this->nV = nV;
        Matrix.assign(nV, std::vector<int>(nV, 0));
    }

    void addEdge(int u, int v, int capacity) {
        Matrix[u][v] = capacity;
    }   

};

class MaxFlowSolver {
    Graph &graph;

    bool findAugmentingPath( int source, int sink, std::vector<int> &parent ) {
        std::vector<bool> Visited(graph.nV, false);
        std::queue<int> Q;
        Q.push(source);
        Visited[source] = true;
        parent[source] = -1;
        while ( !Q.empty() ) {
            int u = Q.front();
            Q.pop();

            for ( int v = 0 ; v < graph.nV; v++ ) {
                if ( !Visited[v] && graph.Matrix[u][v] > 0 ) {
                    parent[v] = u;
                    Visited[v] = true;
                    Q.push(v);
                    if ( v == sink ) return true;
                }
            }
        } 
        return false;
    }

    public:
        MaxFlowSolver(Graph &g) : graph(g) {};

    int fordFulkerson ( int source, int sink ) {
        int maxFlow = 0;
        std::vector<int> Parent(graph.nV);

        while ( findAugmentingPath(source, sink, Parent) ) {
            int pathFlow = INT_MAX;
            for ( int u = sink; u != source ; u = Parent[u] ) {
                int v = Parent[u];
                pathFlow = std::min(pathFlow, graph.Matrix[v][u]);
            }

            for ( int u = sink; u != source ; u = Parent[u] ) {
                int v = Parent[u];
                graph.Matrix[v][u] -= pathFlow;
                graph.Matrix[u][v] += pathFlow;
            }
            maxFlow += pathFlow;
        }
        return maxFlow;
    }
};

int main () {
    
    
    int n = 6;  // Number of vertices
    Graph g(n);

    // Example graph edges (u, v, capacity)
    g.addEdge(0, 1, 16);
    g.addEdge(0, 2, 13);
    g.addEdge(1, 2, 10);
    g.addEdge(1, 3, 12);
    g.addEdge(2, 1, 4);
    g.addEdge(2, 4, 14);
    g.addEdge(3, 2, 9);
    g.addEdge(3, 5, 20);
    g.addEdge(4, 3, 7);
    g.addEdge(4, 5, 4);

    int source = 0, sink = 5;
    std::cout << "Maximum Flow: " << MaxFlowSolver(g).fordFulkerson(source, sink) << "\n";

    return 0;
}
