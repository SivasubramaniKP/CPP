#include <iostream>
#include <vector>
#include <stack>

class Graph {
public:
    int nV, nE;
    std::vector<std::vector<int>> List;
    std::vector<int> Visited;
    std::stack<int> topoStack;
    std::vector<int> recStack;
    Graph(int nV, int nE) {
        this->nV = nV;
        this->nE = nE;
        List.resize(nV);
        Visited.resize(nV, 0);
        recStack.resize(nV, 0);
    }

    void inputGraph() {
        for (int i = 0; i < nE; i++) {
            int u, v;
            std::cin >> u >> v;
            List[u].push_back(v);  // u -> v
        }
    }

    void DFSHelper(int vertex) {
        recStack[vertex] = 1;
        Visited[vertex ] = 1;
        for( int v : List[vertex] ) {
            if ( !Visited[v] ) {
                DFSHelper(v);
            } else if ( recStack[v] ) {
                std::cout << "Cycle detected !!";
                exit(0);
            }
        }
        recStack[vertex] = 0;
        topoStack.push(vertex);
    }

    void topologicalSort() {
        for ( int i = 0 ; i < nV; i++ ) {
            if ( !Visited[i] ) {
                DFSHelper(i);
            }
        }
        std::cout << "topological Sort : ";
        while (!topoStack.empty()) {
            std::cout << topoStack.top() << " ";
            topoStack.pop();
        }
    }
};


int main() {
        int nE, nV;
        std::cin >> nE >> nV;
        Graph graph(nE, nV) ;
        graph.inputGraph();
        graph.topologicalSort();
        return 0;
}

