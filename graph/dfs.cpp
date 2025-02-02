#include <iostream>
#include <stack>
#include <vector>
#include <queue>
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
        Parent.resize(nV, -1); // Setting the parent of node to be unknown
        Distance.resize(nV, 2147483647); // Setting distance to Infinity cuz we dont know if the vertex are connected initially
        Start.resize(nV, 0); // Start and finishing times
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
        /*
            DFS(int vertex) is the utility function for runDFS()
            Recursively calls itself if the neighbours the vertex are not visited
        */
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
        /*
            Main DFS() function :
            runs DFS on every  vertices and update the parent and distance values
        */
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

        /*
            The function categorises the edges
            1. tree edge 
            2. Non tree edge
                i. Forward edge
                ii. Backward edge
                iii. Cross edge
        */
        runDFS();

        std::vector<std::pair<std::pair<int, int>, std::string>> Classifier;
        /* 
            Classifier stores the edge and its category
            Its of the type
            [
                { (1,2), "Backward Edge" },
                { (3,4), "tree edge" }
            ]
        */
        for ( int i = 0 ; i < nV; i++ ) {
            for ( int neighbour : List[i] ) {
                /*
                    One simple trick
                    Imagine a DFS tree
                    the vertices at the top(near the root) has lower starting time and higher finishing times
                    closer the vertex to the root : Higher the finishing time, lower the starting times
                    Farther the vertex from the root : Higher the starting time, lower the finishing times 

                              1
                            /   \
                            2   5
                           / \
                          3  4

                          1 : has the minimum starting time and maximum finishing time

                        Consider the edge 1 -> 5 ( tree edge ) 
                        1 is represented by i 
                        5 is represented by neighbour in the code

                        Start time of 1 should be smaller than 5 and also finishing time of 1 should be greater the 5
                         -> So its a tree edge

                        consider edge in the graph 3 ->1
                        Start time of 3 is greater and finishing time of 1 is greater ( This is exactly what i written in if condition )
                */
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

    /*
        1 - 2
        |   |
        3 - 4

        Execution :
            checkCycle(1)
            CheckCycle(2)
    */
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
                if ( checkCycleHelper(neighbour) ) {
                    return true;
                }
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

    public:
        /*
            Topological Sort...
        */

       void TopologicalSort() {
        resetVisited();
        std::vector<int> inDegree(nV, 0);
        for ( int u = 0; u < nV; u++ ) {
            for ( int v : List[u] ) {
                inDegree[v]++;
            }
        }
        std::queue<int> Q;
        std::vector<int> res;
        int visit = 0;
        for ( int i = 0; i < nV ; i++ ) {
            if ( inDegree[i] == 0 ) Q.push(i);
        } 
        while ( !Q.empty() ) {
            int node = Q.front();
            Q.pop();
            visit++;
            res.push_back(node);
            for ( int v : List[node] ) {
                inDegree[v]--;
                if ( inDegree[v] == 0 ) Q.push(v);
            }
        }
        if ( visit != nV ) {
            std::cout << "Cycle detected \n";
            return;
        }   
        for ( int i : res ) {
            std::cout << i << " ";
        }
       }


        /*
            Topological sort using DFS
        */

       void DFStopologicalSort() {
        resetVisited();
        std::stack<int> res;
        for( int i = 0; i < nV; i++ ) {
            if ( Visited[i] == false ) {
                DFStopologicalSortUtil(i, res);
            }
        }
        std::vector<int> revStack;
        while ( !res.empty() ) {
            revStack.push_back(res.top());
            res.pop();
        }
        for ( int i : revStack ) {
            std::cout << i + 1 << " ";
        }
       }
       private:
        void DFStopologicalSortUtil (int vertex, std::stack<int> &res) {
            Visited[vertex] = true;
            for( int v : List[vertex] ) {
                if ( !Visited[v] ) {
                    DFStopologicalSortUtil(v, res);
                }
            }
            res.push(vertex);
        }

};

int main () {
    Graph * graph = new Graph(6,6);
    graph->inputGraph();
    // graph->CategoriseEdges();
    // graph->SCC();
    // graph->TopologicalSort();
   graph->DFStopologicalSort();

}