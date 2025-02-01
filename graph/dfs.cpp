#include <iostream>
#include <vector>

class Graph {
    public:
    int nE; // Number of edges
    int nV; // Number of vertices

    private:
    std::vector<std::vector<int>> List; // Adjacency list representation of graph
    std::vector<int> Parent;
    std::vector<int> Distance;
    std::vector<int> Start;
    std::vector<int> Finish;
    std::vector<bool> Visited;
    int Time;
    // Create a constructor for the grpah
    // The constructor gets an input of number of vertices and edges as arguement
    // and create adjacency list representation for the graph
    public:
    Graph ( int nE, int nV ) {
        this->nE = nE;
        this->nV = nV;
        Parent.resize(nV, -1);
        Distance.resize(nV, 2147483647);
        Start.resize(nV, 0);
        Finish.resize(nV, 0);
        // Lets input the edges and store it in the list
        List.resize(nV);        
        Visited.resize(nV, 0);
        this->Time = 0;
        
    }
    void inputGraph () {
        std::cout << "Enter the edges in this format 'vertex1 vertex2'" << std::endl;
        // To denote an edge from vertex 1 to 5
        // input
        // 1 5             ---- 1 space 5
        //In this graph im indexing from 1
        for ( int i = 0 ; i < nE; i++ ) {
            int u,v;
            std::cin >> u >> v;
            if ( u > 0 && u <= nV && v > 0 && v <= nV ) {
                List[u-1].push_back(v-1);
                // Add the following line for undirected graph
                // List[v-1].push_back(u-1);
                //This line suggests that the edge is bidirectional
            }
        } 
    }
    void DFS(int vertex) {
        Visited[vertex] = true;        
        Start[vertex] = Time++;
        for ( int i : List[vertex] ) {
            Parent[i] = vertex;
            Distance[i] = 1  + Distance[vertex];
            if ( !Visited[i] ) {
                DFS(i);
            }
        }
        Finish[vertex] = Time++;
    }
    
    void runDFS() {
        for ( int i = 0 ; i < nV; i++ ) {
            if( !Visited[i] ) {
                Parent[i] = -1;
                Distance[i] = 0;
                DFS(i);
            }
        }
    }

    void DisplayGraphInfo() {
        for ( int i = 0 ; i < nV; i++ ) {
            std::cout << "Vertex " << (i + 1) << std::endl;
            std::cout << "Parent : " << Parent[i] + 1 << std::endl;
            std::cout << "Distace : " << Distance[i] << std::endl;
            std::cout << "Neighbours : ";
            for ( int neighbours : List[i] ) {
                std::cout << neighbours + 1 << ", ";
            }
            std::cout << "\nstarting time : " << Start[i] << std::endl;
            std::cout << "Finishing time : " << Finish[i] << std::endl;
            std::cout << "\n\n";
        }
    }

    void CategoriseEdges() {
        runDFS();
        std::vector<std::pair<std::pair<int, int>, std::string>> Classifier;
        for ( int i = 0 ; i < nV; i++ ) {
            for ( int neighbour : List[i] ) {
                if ( Start[i] < Start[neighbour] && Finish[i] > Finish[neighbour] ) {
                    Classifier.push_back({{i,neighbour}, "tree edge"});
                } else if ( Start[i] > Start[neighbour] && Finish[neighbour] > Finish[i] ) {
                    Classifier.push_back({{i, neighbour}, "Backedge"});
                } else if ( Start[neighbour] < Start[i] ) {
                    Classifier.push_back({{i, neighbour}, "cross edge"});
                } else {
                    Classifier.push_back({{i, neighbour}, "Forward edge"});
                }
            }
        }
        for ( std::pair<std::pair<int,int>, std::string> i : Classifier ) {
             std::cout << i.first.first + 1 << "->" << i.first.second + 1 << " : " << i.second << std::endl;
        }
    }
    private:
        void resetVisited() {
            for ( int i = 0 ; i < nV; i++ ) Visited[i] = 0;
        }
    std::vector<int> RecStack;
    public:
    void checkCycle() {
        resetVisited();
        RecStack.assign(nV, 0);

        for ( int i = 0; i < nV; i++ ) {
            if ( !Visited[i] ) {
                if (checkCycleHelper(i)) {
                    std::cout << "Cycle detected" << std::endl;
                    return;
                }
            }
        }
        std::cout << "No cycles \n";
    }
    private:
    bool checkCycleHelper(int vertex) {
        Visited[vertex] = 1;
        RecStack[vertex] = 1;
        for ( int neighbour : List[vertex] ) {
            if ( !Visited[neighbour] ) {
            } else if (RecStack[neighbour]){
                return true;
            }
        }
        RecStack[vertex] = 0;
        return false;
    }

    // Strongly Connected Components:
    /*
        1. Run DFS and number the vertices.
        2. Arrange the vertices in descending order of finishing time
        3. Run DFS on the vertex with maximum finishing time
        3. Transpose the graph
        5. The vertices covered by the DFS forms a strongly connected components
        6. Run DFS until all vertices are covered.
    */

    /*
        function returns the list of strongly connected components
        Component 1 : 1,2,3
        Component 2 : 5,6
        Component 3 : 4
    */
   public: 
   void SCC() {
    resetVisited();
    runDFS();
    std::vector<std::pair<int, int>> timePair;
    for ( int i = 0 ; i < nV ; i++ ) {
        timePair.push_back({i, Finish[i]});
    }   
    for ( int i = 0 ; i < nV - 1; i++ ) {
       for ( int j = 0 ; j < nV - i - 1; j++ ) {
        if ( timePair[j].second < timePair[j + 1].second ) {
            std::pair<int, int> temp = timePair[j];
            timePair[j] = timePair[j+1];
            timePair[j+1] = temp;
        }
       } 
    }

   Graph * transposeGraph = new Graph(nE, nV);
    for ( int u = 0 ; u < nV; u++) {
        for ( int v : List[u] ) {
            transposeGraph->List[v].push_back(u);
        }
    }

    std::vector<std::vector<int>> res =  transposeGraph->SCCDFS();
    for ( int i = 0 ; i < res.size(); i++ ) {
        std:: cout << "cOmponent " << i <<" : ";
        for ( int j : res[i] ) {
            std::cout << j + 1 << " ";
        }
        std::cout << "\n";
    }
   }

    private:
        std::vector<std::vector<int>> SCCDFS() {
            std::vector<std::vector<int>> res;
            for ( int i = 0 ; i < nV; i++ ) {
                
                if ( !Visited[i] ) {
                    std::vector<int> temp;
                    SCCDFSHelper(i, temp);
                    res.push_back(temp);
                }
            }
            return res;
        }

        void SCCDFSHelper(int vertex, std::vector<int>&temp) {
            Visited[vertex] = true;
            temp.push_back(vertex);
            for ( int v : List[vertex] ) {
                if ( !Visited[v] ) {
                    SCCDFSHelper(v, temp);
                }
            }    
        } 
};

int main () {
    Graph * graph = new Graph(9,8);
    graph->inputGraph();
    // graph->CategoriseEdges();
    graph->SCC();
   
}