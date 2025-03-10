#include <iostream>
#include <climits> 
#include <vector>
#include <queue>

class Graph{ 
    public:
    int nE;
    int nV;
    std::vector<std::vector<int>> Matrix;

        Graph ( int nE, int nV ) {
            this->nE = nE;
            this->nV = nV;
            Matrix.assign(nV, std::vector<int>(nV, 0));
        }
        void addEdge(int u, int v, int c) {
            Matrix[u][v] = c;
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
    Graph &graph;
    bool findAugmentingPath(int source, int sink, std::vector<int> &parent) {
        std::vector<bool> Visited(graph.nV, false);
        std::queue<int> Q;
        Q.push(source);
        Visited[source] = true;
        parent[source] = -1;
        while ( !Q.empty() ) {
            int u = Q.front(); Q.pop();
            for ( int v = 0 ; v  < graph.nV; v++ ) {
                if ( !Visited[v] && graph.Matrix[u][v] > 0 ) {
                    Visited[v] = true;
                    Q.push(v);
                    parent[v] = u;
                    if ( v == sink ) return true;
                }
            }
        } 
        return false;
    }

    public:
        std::vector<std::pair<int,int>> minCutEdges;
        MaxFlowSolver(Graph &g) : graph(g) {};
        int FordFulkerson( int source, int sink ) {
            int maxFlow = 0;
            std::vector<int> Parent(graph.nV, -1);
            while ( findAugmentingPath(source, sink, Parent) ) {
                int pathFlow = INT_MAX;
                for ( int u = sink; u != source ; u = Parent[u] ) {
                    int v = Parent[u];
                    pathFlow = std::min(pathFlow, graph.Matrix[v][u]);
                }
                for ( int u = sink; u != source; u = Parent[u] ) {
                    int v = Parent[u];
                    graph.Matrix[u][v] += pathFlow;
                    graph.Matrix[v][u] -= pathFlow;
                }
                maxFlow += pathFlow;
            }
            return maxFlow;
        }
};

int main () {
    int nE,nV;
    std::cin >> nE >> nV;
    Graph graph(nE, nV);
    graph.inputGraph();
    MaxFlowSolver * solver = new MaxFlowSolver(graph);
    std::cout << solver->FordFulkerson(0,5);
    return 0;
}