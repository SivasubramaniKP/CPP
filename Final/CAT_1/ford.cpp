#include <iostream>
#include <queue>
#include <vector>

class Graph {
public:
    int nE;
    int nV;
    std::vector<std::vector<int>> Matrix;
    Graph(int nV) {
        this->nV = nV;
        Matrix.resize(nV, std::vector<int> (nV, 0));
    }
    void inputGraph() {
        for ( int i = 0 ; i < nE; i++ ) {
            int u, v, w;
            std::cin >> u >> v >> w;
            Matrix[u][v] = w;
        }
    }
    void addEdge(int u, int v, int capa) {
        Matrix[u][v] = capa;
    }
};

class MaxFlowSolver {
    Graph &graph;
    Graph originalGraph; 
    bool findAugmentingPath(int source, int sink, std::vector<int> &Parent) {
        std::vector<bool> Visited(graph.nV, false);
        std::queue<int>Q;
        Visited[source] = 1;
        Parent[source] = -1;
        Q.push(source);
        while ( !Q.empty() ) {
            int u = Q.front(); Q.pop();
            for ( int v = 0 ; v < graph.nV; v++ ) {
                if ( !Visited[v] && graph.Matrix[u][v] > 0 ) {
                    Parent[v] = u;
                    Q.push(v);
                    Visited[v] = true;
                    if ( v == sink ) return true;
                }
            }
        }
        return false;
    }

public:
    MaxFlowSolver(Graph &g) : graph(g), originalGraph(g.nV) {
        originalGraph.Matrix = g.Matrix;
    }
    int FordFulkerson(int source, int sink) {
        int maxFlow = 0;
        std::vector<int> Parent(graph.nV);
        while ( findAugmentingPath(source, sink, Parent) ) {
            int pathFlow = INT32_MAX;
            for ( int u = sink ; u != source ; u = Parent[u] ) {
                int v = Parent[u];
                pathFlow = std::min(pathFlow, graph.Matrix[v][u]);
            }
            for ( int u = sink ; u != source; u = Parent[u] ) {
                int v = Parent[u];
                graph.Matrix[v][u] -= pathFlow;
                graph.Matrix[u][v] += pathFlow; 
            }
            maxFlow += pathFlow;
        }
        return maxFlow;
    }

    std::vector<std::pair<int,int>> findMinCut( int source, int sink, Graph OG) {
        std::vector<int> Visited(graph.nV, 0);
        Visited[source] = 1;
        std::queue<int> Q;
        Q.push(source);
        while ( !Q.empty() ) {
            int u = Q.front(); Q.pop();
            for ( int v = 0 ; v < graph.nV; v++ ) {
                if ( !Visited[v] && graph.Matrix[u][v] > 0 ) {
                    Q.push(v);
                    Visited[v] = 1;
                }
            }
        }

        std::vector<std::pair<int,int>> res;
        for ( int u = 0 ; u < graph.nV; u++ ) {
            if ( Visited[u] ) {
                for ( int v = 0 ; v < graph.nV; v++ ) {
                    if ( !Visited[v] &&  originalGraph.Matrix[u][v] > 0) {
                        res.push_back({u,v});
                        std::cout << originalGraph.Matrix[u][v] << "\n";
                    }
                }
            }
        }
        return res;
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
    MaxFlowSolver mfs(g);
    std::cout << "Maximum Flow: " << mfs.FordFulkerson(source, sink) << "\n";
    std::vector<std::pair<int,int>> res = mfs.findMinCut(source, sink, g);
    for ( std::pair<int, int> pair: res ) {
        std::cout << pair.first << "->" << pair.second << "\n";
    }
    return 0;
}
