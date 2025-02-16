#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
class Graph{
    public:
    int nE;
    int nV;
    std::vector<std::vector<int>> List;
    std::vector<int> Parent;
    std::vector<int> Distance;
    std::vector<bool> Visited;
    std::vector<int> StartTime;
    std::vector<int> endTime;
    int Time;
    Graph ( int nE, int nV )  {
        this->nE = nE;
        this->nV = nV;
        List.resize(nV);
        reset();
    } 

    void inputGraph() {
        std::cout << "Enter the edges " << std::endl;
        for ( int i = 0 ; i  < nE ; i++ ) {
            int u , v;
            std::cin >> u >> v;
            List[u-1].push_back(v-1);
            // List[v-1].push_back(u-1);
        }
    }

    void reset() {
        Parent.resize(nV, -1);
        Distance.resize(nV, INT_MAX);
        Visited.resize(nV, false);
        StartTime.assign(nV, 0);
        endTime.assign(nV, 0);
        Time = 0;
        recStack.assign(nV, 0);
    }

    void DFS() {
        reset();
        for ( int i = 0 ; i < nV; i++ ) {
            if ( !Visited[i] ) {
                Visited[i] = true;
                Parent[i] = -1;
                Distance[i] = 0;
                DFSHelper(i);
            }
        }
    }

    void DFSHelper ( int vertex ) {
        Visited[vertex] = true;
        StartTime[vertex] = Time++;
        for ( int v : List[vertex] ) {
            if ( !Visited[v] ) {
                Distance[v] = 1 + Distance[vertex];
                Parent[v] = vertex;
                DFSHelper(v);
            }
        }
        endTime[vertex] = Time++;
    }

    void printDetails () {
        for ( int i = 0 ; i < nV; i++ ) {
            std::cout  << "Vertex " << i + 1 << std::endl;
            std::cout << "Parent " << Parent[i] + 1 << std::endl;
            std::cout << "Distance : " << Distance[i] << std::endl;
            std::cout << "Start time " << StartTime[i] << std::endl;
            std::cout << "End time : " << endTime[i] << std::endl;
            std::cout << "\n\n";
        }
    }

    std::string classifyEdge(int start1, int end1, int start2, int end2) {
        std::string res;
        if ( start1 < start2 && end1 > end2 ) {
            res = ( abs(start1 - start2) == 1 ) ? "Tree edge" : "Forward edge";
        }
        else if ( start1 > start2 && end1 < end2 ) res = "Back edge";
        else if ( start2 > end1 || start1 > end2 ) res = "Cross edge";
        return res;
    }

    void Classify () {
        DFS();
        for ( int u = 0 ; u < nV; u++ ) {
            for ( int v : List[u] ) {
                std::cout << "Edge " << (u) << " to " << (v) << classifyEdge(StartTime[u], endTime[u], StartTime[v], endTime[v]) <<std::endl;
            }
        }
    }

    std::vector<int> recStack;

    void checkCycles() {
        reset();
        for ( int i = 0 ; i < nV; i++ ) {
            if ( !Visited[i] ) {
                if (foo(i)) {
                    std::cout << "Cycle detected" << std::endl;
                    return; 
                } 
            }
        }
        std::cout << "no cycles" << std::endl;
    }

    bool foo( int vertex ) {
        Visited[vertex] = true;
        recStack[vertex] = 1;
        for ( int v : List[vertex] ) {
            if ( !Visited[v] ) {
                if ( foo(v) ) return true; 
            } else if ( recStack[v] == 1 ) {
                return true;
            }
        } 
        recStack[vertex] = 0;
        return false;
    }

    

};

int main () {
    Graph  * graph = new Graph(7,9);
    
    graph->inputGraph();
    // graph->DFS();
    // graph->printDetails();
    graph->checkCycles();
    // graph->Classify();
}
