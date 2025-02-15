#include <iostream>
#include <vector>
#include <climits>
#include <queue>
class Graph{
    int nE;
    int nV;
    std::vector<std::vector<int>> List;
    public:
        Graph( int nE, int nV ) {
           this->nE = nE;
           this->nV = nV;
           List.resize(nV); 
        }

    void inputGraph() {
        std::cout << "Enter the eges " << std::endl;
        int u,v;
        for ( int i = 0; i < nE; i++ ) {
            std::cin >> u >> v;
            List[u-1].push_back(v-1);
            List[v-1].push_back(u-1);
        }
    }

    void BFS() {
        std::vector<int> Parent(nV, -1);
        std::vector<bool> Visited(nV, false);
        std::vector<int> Distance(nV, INT_MAX);
        int verticesVisited = 0;
        std::queue<int> Q;
        
        for ( int i = 0; i < nV; i++ ) {
            if ( Visited[i] == false ) {
                int source = i;
                Q.push(i);
                Visited[i] = true;
                Parent[i] = -1;
                Distance[i] = 0;
                while ( !Q.empty() ) {
                    int node = Q.front(); Q.pop();
                    for ( int v : List[node] ) {
                        if ( !Visited[v] ) {
                            Visited[v] = true;
                            Q.push(v);
                            Parent[v] = node;
                            Distance[v] = 1 + Distance[node];
                        }
                    }
                }
            }
        }
        
        for ( int i = 0 ; i < nV; i++ ) {
            std::cout << "Vertex " << (i + 1) << std::endl;
            std::cout << "Parent = " << Parent[i] + 1 << std::endl;
            std::cout << "Distance = " << Distance[i] << std::endl;
            std::cout << "\n\n";
        }


    }

};


int main () {
    Graph * graph = new Graph(7,5);
    graph->inputGraph();
    graph->BFS();

    return 0;
}