#include <iostream>
#include <queue>
#include <vector>
#include <climits>

class Graph {
    public:
    int nE;int nV;
    std::vector<std::vector<int>> Matrix;
    Graph(int nE, int nV) {
        this->nE = nE;
        this->nV = nV;
        Matrix.assign(nV, std::vector<int>(nV, 0));
    }
    void inputGraph() {
        for( int i = 0 ; i < nE; i++ ) {
            int u,v,c;
            std::cin >> u >> v >> c;
            Matrix[u][v] = c;
        }
    }
};

class MaxFlowSolver {
    public:
    Graph &graph;
    MaxFlowSolver(Graph &g) : graph(g) {};
    bool findAugmentingPath( int source, int sink, std::vector<int> &parent ) {
        
        std::vector<bool> Visited(graph.nV, false);
        std::queue<int> Q;  
        Q.push(source);
        parent[source] = -1;
        Visited[source] = true;
        while ( !Q.empty() ) {
            int u = Q.front(); Q.pop();
            for ( int v = 0 ; v < graph.nV ; v++ ) {
                if ( !Visited[v] && graph.Matrix[u][v] > 0 ) {
                    Visited[v] = true;
                    parent[v] = u;
                    Q.push(v);
                    if ( v == sink ) return true;
                }
            }
        } 
        return false;   
    }

    int FordFulkerson ( int source, int sink ) {
        int maxFlow = 0;
        std::vector<int> Parent(graph.nV, -1);
        while ( findAugmentingPath(source, sink, Parent) ) {
            int pathFlow = INT_MAX;
            for ( int v = sink ; v != source ; v = Parent[v] ) {
                int u = Parent[v];
                pathFlow = std::min(pathFlow, graph.Matrix[u][v]);
            }
            for ( int v = sink; v != source; v = Parent[v] ) {
                int u = Parent[v];
                graph.Matrix[u][v] -= pathFlow;
                graph.Matrix[v][u] += pathFlow;
            }
            std::cout << "Path flow = " << pathFlow << "\n";
            maxFlow += pathFlow;
        }
        return maxFlow;
    }
};

int main () {
    int nE, nV;
    std::cin >> nE >> nV;
    Graph graph(nE, nV);
    graph.inputGraph();
    MaxFlowSolver solver(graph);
    std::cout << solver.FordFulkerson(0, 5);
    return 0;
}