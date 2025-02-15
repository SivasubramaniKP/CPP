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

    void findShortestPath(int source, int destination) {
        std::vector<int> Parent(nV, -1);
        std::vector<int> Distance(nV, INT_MAX);
        std::vector<bool> Visited(nV, false);
        std::queue<int> Q;
        
        Q.push(source);
        Parent[source] = -1;
        Distance[source] = 0;
        Visited[source] = true;
        while ( !Q.empty() ) {
            int node = Q.front(); Q.pop();
            for ( int v : List[node] ) {
                if ( !Visited[v] ) {
                    Visited[v] = true;
                    Distance[v] = 1 + Distance[node];
                    Parent[v] = node;
                    Q.push(v);
                }
            }
        }
        if ( Distance[destination] == INT_MAX ) {
            std::cout << "The graph is disconnected cannot reach Destination from source \n";
        }
        std::vector<int> Path;
        int cur = destination;
        while ( cur != -1 ) {
            Path.push_back(cur);
            cur = Parent[cur];
        }
        for ( int i : Path ) {
            std::cout << i  << " <- ";
        } 

    }

    void findComponents() {

        std::vector<int> Parent(nV, -1);
        std::vector<int> Distance(nV, INT_MAX);
        std::vector<bool> Visited(nV, false);
        std::vector<std::vector<int>> Components;
        for ( int i = 0 ; i < nV; i++ ) {
            if ( !Visited[i] ) {
                std::vector<int> curComponents;
                int source = i;
                Parent[source] = -1;
                Distance[source] = 0;
                Visited[source] = true;
                curComponents.push_back(source);
                std::queue<int> Q;
                Q.push(source);
                while ( !Q.empty() ) {
                    int node = Q.front();
                    Q.pop();
                    for ( int v : List[node] ) {
                        if ( !Visited[v] ) {
                            Parent[v] = node;
                            Distance[v] = 1 + Distance[node];
                            Visited[v] = true;
                            curComponents.push_back(v);
                            Q.push(v);
                        }
                    } 
                }

                Components.push_back(curComponents);
            }
        }
        for ( std::vector<int> comp : Components ) {
            for ( int v : comp ) {
                std::cout << v + 1 << " ";
            }
            std::cout << "\n";
        } 

    }

    void detectCycle() {
        std::queue<std::pair<int,int>> Q;
        std::vector<bool> Visited(nV, false);
        std::vector<int> Parent(nV, -1);
        std::vector<int> Distance(nV, INT_MAX);
        for ( int i = 0 ; i < nV; i++ ) {
            if ( !Visited[i] ) {
                Parent[i] = -1;
                Distance[i] = 0;
                Visited[i] = true;
                Q.push({i, -1});
                while ( !Q.empty() ) {
                    int node = Q.front().first;
                    int parent = Q.front().second;
                    Q.pop();
                    for ( int v : List[node] ) {
                        if ( !Visited[v] ) {
                            Visited[v] = true;
                            Parent[v] = node;
                            Distance[v] = 1 + Distance[node];
                            Q.push({v, node});
                        } else if ( v != parent ) {
                            std::cout << "Cycle detected at node " << v << " and " << node << std::endl;
                            return;
                        }
                    }
                }
            }
        } 
        std::cout << "No cycles " << std::endl;
    }

};


int main () {
    Graph * graph = new Graph(7,5);
    graph->inputGraph();
    // graph->findShortestPath(0,5);
    // graph->findComponents();
    graph->detectCycle();
    return 0;
}