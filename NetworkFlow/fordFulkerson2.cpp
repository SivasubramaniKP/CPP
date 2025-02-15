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
    Graph &graph;

    bool findAugmentingPath ( int source, int sink, std::vector<int> &parent ) {
        std::vector<bool> visited(graph.nV, 0);
        std::queue<int> q;
        q.push(source);
        visited[source] = true;
        parent[source] = -1;
        while ( !q.empty() ) {
            int u  = q.front(); q.pop();
            for ( int v = 0; v < graph.nV; v++ ) {
                if ( !visited[v] && graph.Matrix[u][v] > 0 ) {
                    parent[v] = u;
                    visited[v] = true;
                    q.push(v);
                    if ( v == sink ) return true;
                }
            }
        }
        return false;
    } 
    public:    
    MaxFlowSolver( Graph &g ) : graph(g) {}
    int fordFulkerson (int source,int sink) {
        int res = 0;
        std::vector<int> Parent(graph.nV);
        while ( findAugmentingPath(source, sink, Parent) ) {

            int maxFlow = INT_MAX;
            for ( int u = sink; u != source; u = Parent[u] ) {
                int v = Parent[u];
                maxFlow = std::min(maxFlow, graph.Matrix[v][u]);
            }
            for ( int v = sink; v != source; v = Parent[v] ) {
                int u = Parent[v];
                graph.Matrix[u][v] -= maxFlow;
                graph.Matrix[v][u] += maxFlow;
            }
            res += maxFlow;
        }
        return res;
    } 

};
int main() {
    int nV = 9;
    Graph g(nV);

    g.addEdge(0, 1, 6);
    g.addEdge(0, 2, 1);
    g.addEdge(0, 3, 10);
    g.addEdge(1, 2, 2);
    g.addEdge(3, 2, 2);
    g.addEdge(1, 4, 4);
    g.addEdge(1, 5, 1);
    g.addEdge(2, 5, 20);
    g.addEdge(3, 6, 5);
    g.addEdge(4, 5, 2);

    g.addEdge(5, 6, 6);
    g.addEdge(4, 7, 5);
    g.addEdge(5, 7, 10);
    g.addEdge(6, 8, 4);

    g.addEdge(7, 8, 12);
    MaxFlowSolver solver(g);
    std::cout << "Maximum Flow: " << solver.fordFulkerson(0, 5) << std::endl;

    return 0;
}