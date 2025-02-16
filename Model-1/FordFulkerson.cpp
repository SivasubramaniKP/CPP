#include <iostream>
#include <vector>
#include <queue>
#include <climits>
class Graph {
    public:
    int nE;
    int nV;
    std::vector<std::vector<int>> Matrix;

    Graph( int nV ) {
        this->nV = nV;
        Matrix.assign(nV, std::vector<int>(nV, 0));
    }
    
    void addEdge ( int u, int v, int capacity ) {
        Matrix[u][v] = capacity;
    } 
    void printGraph() {
        std::cout << "Residual Graph:\n";
        for (int i = 0; i < nV; i++) {
            for (int j = 0; j < nV; j++) {
                std::cout << Matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

class MaxFlowSolver {
    Graph &g;
    bool findAugmentingPath(int source, int sink, std::vector<int> &parent) {
        std::vector<bool> Visited(g.nV, false);
        std::queue<int> Q;
        Q.push(source);
        Visited[source] = true;
        parent[source] = -1;

        while ( !Q.empty() ) {
            int u = Q.front(); Q.pop();
            for ( int v = 0; v < g.nV ; v++ ) {
                if ( !Visited[v] && g.Matrix[u][v] > 0 ) {
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
        MaxFlowSolver(Graph &g) : g(g) {};
        int FordFulkerson ( int source, int sink ) {
            int maxFlow = 0;
            std::vector<int> parent(g.nV);

            while ( findAugmentingPath(source, sink, parent) ) {
                int pathFlow = INT_MAX;
                for ( int u = sink ; u != source ; u = parent[u] ) {
                    int v = parent[u];
                    pathFlow = std::min(pathFlow, g.Matrix[v][u]);
                } 
                for ( int u = sink ; u != source ; u = parent[u] ) {
                    int v = parent[u];
                    g.Matrix[v][u] -= pathFlow;
                    g.Matrix[u][v] += pathFlow;
                }
                maxFlow += pathFlow;
            }
            return maxFlow;
        } 
};

int main() {
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
    std::cout << "Maximum Flow: " << MaxFlowSolver(g).FordFulkerson(source, sink) << "\n";

    return 0;
}