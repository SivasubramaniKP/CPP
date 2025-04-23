#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
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
    int Time;
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
        Time = 0;
    }
    void reset() {
        Parent.resize(nV, -1);
        Distance.resize(nV, INT_MAX);
        Visited.resize(nV, 0);
        StartTime.resize(nV, 0);
        EndTime.resize(nV, 0);
        Time = 0;
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

    void DFS() {
        for ( int i = 0 ; i < nV; i++ ) {
            if ( !Visited[i] ) {
                DFSHelper(i);
            }
        }
    }

    void DFSHelper(int vertex) {
        StartTime[vertex] = Time++;
        Visited[vertex] = 1;
        for ( int v : List[vertex] ) {
            if  ( !Visited[v] ) {
                DFSHelper(v);
            }
        }
        EndTime[vertex] = Time++;
    }

    void StronglyConnectedComponents() {
        reset();
        DFS();
        std::vector<std::pair<int, int>> timePair;
        for ( int i = 0 ; i < nV; i++ ) {
            timePair.push_back({EndTime[i], i});
        }

       std::sort(timePair.begin(), timePair.end(), std::greater<std::pair<int, int>>()); 

        Graph transposed(nE, nV);
        for ( int i = 0 ; i < nV; i++ ) {
            for ( int v : List[i] ) {
                transposed.List[v].push_back(i);
            }
        }
        
        std::vector<std::vector<int>> res;

        for ( int i = 0 ; i < nV; i++ ) {
            int curNode = timePair[i].second;
            if ( !transposed.Visited[curNode] ) {
                std::vector<int> Component;
                transposed.SCCDFS(curNode,Component);
                res.push_back(Component);
            }
        }
        for ( std::vector<int> a: res ) {
            std::cout << "Componenet : " ;
            for ( int i : a ) {
                std::cout << i << " ";
            }
            std::cout << "\n";
        } 
    }

    void SCCDFS(int vertex, std::vector<int> &Component) {
        Visited[vertex] = 1;
        Component.push_back(vertex);
        for ( int v : List[vertex] ) {
            if ( !Visited[v] ) {
                SCCDFS(v, Component);
            }
        }
    }


};


int main() {
        int nE, nV;
        std::cin >> nE >> nV;
        Graph graph(nE, nV) ;
        graph.inputGraph();
        graph.StronglyConnectedComponents();
        return 0;
}