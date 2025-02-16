#include<iostream>
#include <vector>
#include <queue>
#include <climits>

class Graph{
    public:
    int nE;
    int nV;
    std::vector<std::vector<int>> Matrix;

    Graph(int nV){
        this->nV = nV;
        Matrix.resize(nV, std::vector<int>(nV, 0));
    }

    void addEdge ( int u , int v ) {
        Matrix[u][v] = 1;
    } 
};

class MaxFlowSolver {
    Graph &graph;

    bool findAugmentingPath(int source, int sink, std::vector<int> &Parent) {
        std::vector<int> Visited(graph.nV, false);
        std::queue<int> Q;
        Q.push(source);
        Visited[source] = true;
        Parent[source] = -1;


        while ( !Q.empty() ) {
            int u = Q.front(); Q.pop();

            for ( int v = 0 ; v < graph.nV; v++ ) {
                if ( !Visited[v] && graph.Matrix[u][v] > 0 ) {
                    Visited[v] = true;
                    Parent[v] = u;
                    Q.push(v);
                    if ( v == sink ) return true;
                }
            }
        } 

        return false;
    }

    public:
        MaxFlowSolver(Graph &graph) : graph(graph) {}; 
    
        int FordFulkerson(int source, int sink ) {
            std::vector<int> Parent(graph.nV);  
            int MaxFlow = 0;

            while ( findAugmentingPath(source, sink, Parent) ) {

                int pathFlow = INT_MAX;
                for ( int u = sink ; u != source; u = Parent[u] ) {
                    int v = Parent[u];
                    pathFlow = std::min(pathFlow, graph.Matrix[v][u]);
                }

                for ( int u = sink; u != source; u = Parent[u] ) {
                    int v = Parent[u];
                    graph.Matrix[v][u] -= pathFlow;
                    graph.Matrix[u][v] += pathFlow;
            
                }
                MaxFlow += pathFlow;
            }
            return MaxFlow;
        }
};

int main () {
    int left = 3;
    int right = 3;
    int source = 0, sink = left + right + 1;

    Graph graph(left + right + 2);

    for ( int i = 1 ; i <= left ; i++ ) {
        graph.addEdge(source, i);
    }
    for ( int i = left + 1; i <= left + right; i++ ) {
        graph.addEdge(i, sink);
    }
    graph.addEdge(1, 4);  // U1 -> V1
    graph.addEdge(1, 5);  // U1 -> V2
    graph.addEdge(2, 4);  // U2 -> V1
    graph.addEdge(2, 6);  // U2 -> V3
    graph.addEdge(3, 5);  // U3 -> V2
    graph.addEdge(3, 6);  // U3 -> V3

    MaxFlowSolver solver(graph);
    std::cout << "Maximum Bipartite matching : " << solver.FordFulkerson(source, sink) << std::endl;
    return 0;
}
