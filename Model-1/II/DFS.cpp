#include <iostream>
#include <vector>
#include <stack>
#include <climits>
#include <queue>
class Graph {
    public:
    int nE;
    int nV;
    std::vector<std::vector<int>> List;

    Graph ( int nE, int nV ) {
        this->nE = nE;
        this->nV = nV;
        List.resize(nV);
    }

    void addEdge(int v1, int v2) {
        if ( v1 <= nV and v2 <= nV ) {
            List[v1 - 1].push_back(v2 - 1);
            // List[v2 - 1].push_back(v1 - 1);
        }
    }

    void inputGraph() {
        std::cout << "Enter the graph in this format v1 v2 " << std::endl;
        for ( int i = 0; i < nE; i++ ) {
            int v1, v2;
            std::cin >> v1 >> v2;
            addEdge(v1, v2);
        }  
    }

    std::vector<int> Parent;
    std::vector<int> Distance;
    std::vector<int> Start;
    std::vector<int> Finish;
    std::vector<bool> Visited;
    int time = 0;
    void reset () {
        Parent.assign(nV, -1);
        Distance.assign(nV, INT_MAX);
        Start.assign(nV, 0);
        Finish.assign(nV, 0);
        Visited.assign(nV, false);
        time = 0;
        recStack.assign(nV, 0);
    }

    void DFS() {
        reset();
        for ( int i = 0; i < nV; i++ ) {
            if ( !Visited[i] ) {
                Distance[i] = 0;
                dfs(i);
            }
        }
    }

    void dfs( int vertex ) {
        Visited[vertex] = true;
        Start[vertex] = time++;
        for ( int v : List[vertex] ) {
            if ( !Visited[v] ) {
                Distance[v] = 1 + Distance[vertex];
                Parent[v] = vertex;
                dfs(v);
            }
        }
        Finish[vertex] = time++;
    } 

    void printDetails() {
        for ( int i = 0 ; i < nV; i++ ) {
            std::cout << "Vertex " << i + 1 << std::endl;
            std::cout << "Parent " << Parent[i] + 1 << "\n";  
            std::cout << "Distance " << Distance[i] << "\n";
            std::cout << "Start Time : " << Start[i] << "\n";
            std::cout << "End Time : " << Finish[i] << "\n";
            std::cout << "\n\n";
        }
    }
    void reverseGraph() {
        std::vector<std::vector<int>> adjGraph;
        adjGraph.resize(nV);
        for ( int u = 0; u < nV; u++ ) {
            for ( int v : List[u] ) {
                adjGraph[v].push_back(u);
            }
        }
        List = adjGraph;
    }
    std::vector<int> Components;
    void StronglyConnectedComponents(){
        reset();
        DFS();
        printDetails();
        std::queue<int> Order;
        for ( int i = 0; i < nV ; i++ ) {
            int max = INT_MIN;
            int maxIndex = -1;
            for ( int j = 0 ; j < nV ; j++ ) {
                if ( Finish[j] > max ) {
                    max = Finish[j];
                    maxIndex = j;
                }
            }
            Finish[maxIndex] = INT_MIN;
            Order.push(maxIndex);
        }
        reverseGraph();
        Components.resize(nV, 0);
        Visited.assign(nV, false);
        int compNo = 0;
        while ( !Order.empty() ) {
            int vertex = Order.front(); Order.pop();
            if ( !Visited[vertex] ) {
                SCCDFS(vertex, compNo++);
            }
        } 
        for ( int i = 0 ; i < nV ; i++ ) {
            std::cout << "Component of " << i + 1 << " is " << Components[i] << std::endl;
        }
    }
    
    void SCCDFS( int vertex, int compNo ) {
        Visited[vertex] = true;
        Components[vertex] = compNo;
        for ( int v : List[vertex] ) {
            if ( !Visited[v] ) {
                SCCDFS(v, compNo);
            }
        }
    }

    std::vector<int> recStack;

    // void detectCycle() {
    //     reset();
    //     for ( int i = 0 ; i < nV; i++ ) {
    //         if ( !Visited[i] ) {
    //             if ( cycleDFS(i) ) {
    //                 std::cout << "Cycle detected" << "\n";
    //                 return;
    //             }
    //         }
    //     }
    //     std::cout << "No cycles \n"; 
    // }
    // bool cycleDFS( int vertex ) {
    //     Visited[vertex] = true;
    //     recStack[vertex] = true;
    //     for ( int u : List[vertex] ) {
    //         if ( !Visited[u] ) {
    //             if ( cycleDFS(u) ) return true;
    //         } else if ( recStack[u] == 1 ) {
    //             return true;    
    //         }
    //     }
    //     recStack[vertex] = 0;
    //     return false;
    // }


    void detectCycles () {
        reset();
        for ( int i = 0 ; i < nV; i++ ) 
        {
            if ( !Visited[i] ) {
                if ( cycleDFS(i) ) {
                    std::cout << "Cycle detected \n";
                    return;
                }
            }
        }
        std::cout << "No cycles\n";
        return;
    }

    bool cycleDFS(int vertex) {
        recStack[vertex] = 1;
        Visited[vertex] = true;
        for ( int v: List[vertex] ) {
            if ( !Visited[v] ) {
                if ( cycleDFS(v) ) return true;
            } else if ( recStack[v] == 1 ) return true;
        }
        recStack[vertex] = 0;
        return false;

    }







    std::string classifyEdge(int Start1, int Start2, int End1, int End2) {
        std::string res;
        if ( Start1 < Start2 && End1 > End2 ) {
            res = ( abs(End1 - End2) == 1 ) ? "Tree Edge" : "Forward edge";
        } else if ( Start1 > Start2 && End1 < End2 ) res = "Back edge";
        else  res = "Cross Edge";
        return res;
    }

    void classifyEdges() {
        reset();
        DFS();
        for ( int i = 0 ; i < nV; i++ ) {
            for ( int v : List[i] ) {
                std::cout << "Edge from " << i + 1 << " to " << v + 1 << " is " << classifyEdge(Start[i], Start[v], Finish[i], Finish[v]) << "\n";
            }
        }
    }


    void TopologicalSort () {
        std::vector<int> Indegree(nV, 0);
        reset();
        for ( int i = 0 ; i < nV; i++ ) {
            for ( int v : List[i] ) {
                Indegree[v]++;
            }
        }
        std::queue<int> Q;
        std::vector<int> res;
        for ( int i = 0 ; i < nV; i++ ) {
            if ( Indegree[i] == 0 ) Q.push(i);
        }
        while ( !Q.empty() ) {
            int popped = Q.front(); Q.pop();
            res.push_back(popped);
            for ( int v : List[popped] ) {
                Indegree[v] -= 1;
                if ( Indegree[v] == 0 ) {
                    Q.push(v);
                }
            }
        }
        std::cout << "Topological Sorting Orderd : \n";
        for ( int i = 0 ; i < nV; i++ ) {
            std::cout << res[i] << " ";
        }
    }

};



int main () {
    int nE, nV;
    std::cin >> nE >> nV;
    Graph * graph = new Graph(nE, nV);
    graph->inputGraph();
    // graph->DFS();
    // graph->printDetails();
    // graph->StronglyConnectedComponents();
    // graph->detectCycles();
    // graph->classifyEdges();
    graph->TopologicalSort();
    return 0;
}