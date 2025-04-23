#include <iostream>
#include <vector>
#include <queue>
#include <climits>
class Graph
{
public:
    int nE;
    int nV;
    std::vector<std::vector<int>> List;
    std::vector<int> Parent;
    std::vector<int> Distance;
    std::vector<int> Visited;
    Graph(int nE, int nV)
    {
        this->nE = nE;
        this->nV = nV;
        List.resize(nV);
        Parent.resize(nV, -1);
        Distance.resize(nV, INT_MAX);
        Visited.resize(nV, 0);
    }
    void inputGraph()
    {
        for (int i = 0; i < nE; i++)
        {
            int u, v;
            std::cin >> u >> v;
            List[u].push_back(v);
        }
    }

    void TopologicalSort() {
        std::vector<int> Indegree(nV, 0);
        for ( int u = 0; u < nV ; u++ ) {
            for ( int v : List[u] ) {
                Indegree[v] += 1;
            }
        }
        std::queue<int> Q;
        for ( int i = 0 ; i < nV; i++ ) {
            if ( Indegree[i] == 0 ) Q.push(i);
        }
        if ( Q.empty() ) {
            std::cout << "Cycle detected !!";
            exit(0);
        }
        while ( !Q.empty() ) {
            int u = Q.front();
            Q.pop();
            std::cout << u << " ";
            for ( int v : List[u] ) {
                Indegree[v] -= 1;
                if ( Indegree[v] == 0 ) Q.push(v);
            }
        }
    }

};

int main() {
        int nE, nV;
        std::cin >> nE >> nV;
        Graph graph(nE, nV) ;
        graph.inputGraph();
        graph.TopologicalSort();
        return 0;
}

