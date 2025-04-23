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
    std::vector<int> StartTime;
    std::vector<int> EndTime;
    int TIME;
    Graph(int nE, int nV)
    {
        this->nE = nE;
        this->nV = nV;
        List.resize(nV);
        Parent.resize(nV, -1);
        Distance.resize(nV, INT_MAX);
        Visited.resize(nV, 0);
        StartTime.resize(nV, 0);
        EndTime.resize(nV, 0);
        TIME = 0;
    }
    void inputGraph()
    {
        for (int i = 0; i < nE; i++)
        {
            int u, v;
            std::cin >> u >> v;
            List[u].push_back(v);
            // List[v].push_back(u);
        }
    }
    void reset()
    {
        TIME = 0;
        StartTime.resize(nV, 0);
        EndTime.resize(nV, 0);
        Parent.resize(nV, -1);
        Distance.resize(nV, -1);
        Visited.resize(nV, -1);
    }
    void DFS() {
        reset();
        for ( int i = 0; i < nV; i++ ) {
            if ( !Visited[i] ) {
                Distance[i] = 0;
                DFSHelper(i);
            }
        }
    }

    void DFSHelper (int vertex) {
        Visited[vertex] = 1;
        StartTime[vertex] = TIME++;
        for ( int v : List[vertex] ) {
            if ( !Visited[v] ) {
                Distance[v] = 1 + Distance[vertex];
                DFSHelper(v);
            }
        }
        EndTime[vertex] = TIME++;
    }
    void UndirectedDetectCycle() {
        reset();
        for ( int i = 0; i < nV; i++ ) {
            if ( !Visited[i] ) {
                if ( Undirected_Detect_Cycle_Helper(i, -1) ) {
                    std::cout << "Cycle Detected\n";
                    return;
                }
            }
        }
        std::cout << "No cycles\n";
    }

    bool Undirected_Detect_Cycle_Helper(int vertex, int parent) {
        Visited[vertex] = 1;
        for( int v : List[vertex] ) {
            if ( !Visited[v] ) {
                if( Undirected_Detect_Cycle_Helper(v, vertex) ) {
                    return true;
                }
            } else if ( v != parent ) {
                std::cout << "cycle edge between : " << v << " and " << vertex << "\n";
                return true;
            }
        }
        return false;
    }

    std::vector<int> restack;

    void DirectedDetectCycle() {
        reset();
        restack.resize(nV, 0); 
        for( int i = 0 ; i < nV; i++ ) {
            if ( !Visited[i]  ) {
                if( Directed_DFS_Helper(i) ) {
                    std::cout << "Cycle detected\n";
                    return;
                }
            }
        }
        std::cout << "No cycles\n";
    }
    bool Directed_DFS_Helper(int vertex) {
        restack[vertex] =1;
        Visited[vertex] = 1;
        for( int v : List[vertex] ) {
            if ( !Visited[v] ) {
                if ( Directed_DFS_Helper(v) ) {
                    return true;
                }
            } else if ( restack[v] ) {
                std::cout << "BAck edge between " << v << " and " << vertex << "\n";
                return true;
            }
        }
        restack[vertex] = 0;
        return false;
    }
};

int main() {
        int nE, nV;
        std::cin >> nE >> nV;
        Graph graph(nE, nV) ;
        graph.inputGraph();
        // graph.UndirectedDetectCycle();
        graph.DirectedDetectCycle();
        return 0;
}

