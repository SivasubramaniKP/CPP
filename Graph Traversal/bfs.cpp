#include <iostream>
#include <vector>
#include <queue>


class Graph {
    public:
    int nE; // Number of edges
    int nV; // Number of vertices

    std::vector<std::vector<int>> List; // Adjacency list representation of graph
    std::vector<int> Parent;
    std::vector<int> Distance;
    // Create a constructor for the grpah
    // The constructor gets an input of number of vertices and edges as arguement
    // and create adjacency list representation for the graph

    Graph ( int nE, int nV ) {
        this->nE = nE;
        this->nV = nV;

        // Lets input the edges and store it in the list
        List.resize(nV);
        
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
                List[v-1].push_back(u-1);
                //This line suggests that the edge is bidirectional
            }
        } 
    }

    void BFS ( int Source ) {

        // This function updates the Parent and distance vectors
        // by following BFS traversal 
        // Starting at the Source Vertex

        Parent.resize(nV);
        Distance.resize(nV);

        // Resize the parent and distance vector to hold nV number of entries
        // for each vertex

        // Initialize the parent and distance vectors.

        for ( int i = 0; i < nV; i++ ) {
            Parent[i] = -1;          // Parent of each vertex is unknown
            Distance[i] = 2147483647; // We dont know the distance of the vertex from the Source vertex so the distance of each vertex be at infinite distance
        }

        // Distance of Source vertex is Zero 

        Distance[Source - 1] = 0;
        // Source - 1 because the indexing starts with 0

        std::queue<int> Q;
        // C++ comes with an inbuild Queue data structure
        // q.empty() returns an boolean whether the queue is empty or not ---- true : Queue is empty
        // q.push(10) : Enqueues 10 to the queue
        // q.pop() : Dequeue the queue
        // Q.front() : returns the element which is at the top of the queue
        // Enqueue the Source vertex to the Queue

        std::vector<int> Visited(nV, 0);

        Q.push(Source - 1);
        while ( !Q.empty() ) {

            // Dequeue 
            int node = Q.front();
            Q.pop();

            // Mark the node as visited
            Visited[node] = 1;
            // Find the neighbouring vertex
            // To find the neighbouring vertices, traverse the node'th row of Adjacency list
            for ( int i = 0; i < List[node].size(); i++ ) {

                // If the vertex is unvisited 
                if ( Visited [List[node].at(i)] == 0 ) {
                        Q.push(List[node].at(i));
                        Parent[List[node].at(i)] = node;
                        Distance[List[node].at(i)] = 1 + Distance[node];
                }
            }              
            
        }

    } 

    void printParentDistance() {
        std::cout << "\n\n";
        std::cout << "Parent Vector";
            for ( int i = 0 ; i < nV; i++ ) {
                std::cout << i + 1 << ": " << Parent[i] + 1<< std::endl;
            }
            std::cout << "\n\n Distances : \n";

            for ( int i = 0 ; i < nV; i++ ) {
                std::cout << i + 1 << ": " << Distance[i] << std::endl;
            } 
    }
    
    void findShortestDistance(int source, int destination) {

        // Function takes the source and destination vertices as input
        // and prints the shortest distance and the path
        BFS(source);
        
        int shortestDistance = -1;
        /*
            Start at the destination
            Go to the parent of the destination vertex

            follow these steps till you reach the source
        */ 

       int curVertex = destination - 1; // destination - 1 cuz of zero indexing
       std::vector<int> Path; 

       while ( curVertex != source - 1 && Parent[curVertex] != -1 ) { // Move the curVertex to the parent till the source vertex is reached
       // any one of the condition is enough but im dumb
        Path.push_back(curVertex); // push the curVertex
        curVertex = Parent[curVertex]; 

        // NOTE : We get the Path in reverse order
       }
       Path.push_back(source - 1);
        // Finally add the source vertex
        // cuz we exited the loop when we hit the source


        // Im just printing the path.. So print the path in reverse by reverse indexing
        
        for ( int i = Path.size() - 1; i >= 0 ; i-- ) {
            std::cout << Path[i] + 1<< " ->";
        }
    } 

    void findNumberOfComponents() {

        int nComponents = 0;
        std::vector<std::vector<int>> Components;

        /*
            Choose any arbitrary vertex 
            run BFS
            the components connected by BFS forms a component

            Check the vertex which doesnt have parent
            run bfs on that vertex that doesnt have a parent

            Continue these steps 
        */

       // Lets start with vertex 1 i.e., 0 according to zero indexing

        // We can reduce the number of lines by calling the preexisting BFS method
        // But I should modify the code so that it updates the component number


        // If somebody modifies the BFS function please make a pull request
        
        std::vector<int> Visited(nV, 0);

        // Outer loop runs BFS on every vertex if it is not visited yet
        for ( int source = 0 ; source < nV ; source++ )  { 
            if ( Visited[source] == 0 ) {

            // If any unvisited vertex found => then its a new component
            // increment the number of Components
            nComponents++;
            // In C++ resize is used to dynamically (r)allocate memory
            /*
                std::vector<std::vector<int>> Component
                Component is an "Array of array"

                its used to separate the vertices based on the component

                [
                    [1,2,3], --> 1 , 2, 3 forms a component
                    [4,5],   ---> 4, 5 forms a component
                    [6],  so on
                ]

                initially Component will be like
                [
                ]
                No elements iniside it

                if we tried to access the 0th index it results in an Segmentation fault


                So Component.resize(1) adds an extra vector to the Component Array of array
                after resize the component array will be like
                [
                    []
                ]
                Now we can access the 0th index

            */
            Components.resize(nComponents);
            // Normal BFS
            std::queue<int> Q;
            Q.push(source);
            Visited[source] = 1;
            while ( !Q.empty() ) {
                int node = Q.front();
                Q.pop();
                Components[nComponents - 1].push_back(node);
                for ( int neighbour : List[node] ) {
                    if ( Visited[neighbour] == 0 ) {
                        Q.push(neighbour);
                        Visited[neighbour] = 1;
                    }
                }
            }
            }

            /*After 1 iteration vertices connected by vertex 0 are visited
            Now Components array would be
            [
              [1, 2, 3]
            ]*/
            
            /*

                Now the source (outer loop) will change
                source = 2
                Since 2 is already visited i.e., visited[source] = 1
                2 is skipped

                Next source = 4 is executed
                BFS on 4 is run 
                So on 
            */
        }
        std::cout << "\nNo of components = " << nComponents;
        for (int i = 0; i < nComponents; i++) {
            std::cout << "Component " << i + 1 << ": ";
            for (int node : Components[i]) {
                std::cout << node + 1 << " ";
        }
        std::cout << "\n";
    }
    }

    void checkCycle() {
        // Function to print if there is a cycle in the graph
        // Topological Sort Method
        /*
            There is no Cycle in the graph if there is a valid topological ordering
            cuz we know that topological sort only works on Directed ACYCLIC Graphs

            1. Find the indegree of all the nodes
            2. Push the vertices that have indegree of zero to a queue
            3. till Queue is empty
                i. dequeue to get the vertex with indegree of 0
                ii. Reduce the indegree of its neighbours by 1.
                iii. If some of the neighbour's indegree becomes zero, add it to the queue
                iv. Repeat
            4. If all vertices are visited, then no cycle
        */
       int Visited = 0;
       std::queue<int> queue;
       std::vector<int> indegree(nV, 0);

       // Find the indegree of each node 

       // let take example of graph
       // 1 - 2 - 3 - 4
       // An acyclic graph
        for ( int i = 0 ; i < nV; i++ ) {       // For i = 0
            for ( int neighbours : List[i] ) {  // neighbours will iterate over 1
                indegree[neighbours]++;         // Indegree of 1 will increase
            }
        }

        // Topological sort starts with the vertex with indegree of zero.
        // So find the vertices with indegree of zero
        for ( int i = 0; i < nV; i++ ) {
            if ( indegree[i] == 0 ) {
                queue.push(i);
            }
        }

    
        while ( !queue.empty() ) {
            int node = queue.front();
            queue.pop();
            Visited++;              // Mark the Vertex as visited

            for ( int v : List[node] ) {     //  Update the indegree of its neighbouring vertices. i.e., when 1 completes
                                            // We should update the indegree of 2 since it decreases by 1 
                indegree[v]--;
                if ( indegree[v] == 0 ) {   // If the update vertex's indegree become zero add it to the queue
                    queue.push(v);
                }
            }
        }  


        // If topological sort is successful, then all vertices would have  been visited So 
        // by definintion of a DAG, the given graph is acyclic 
        if ( Visited == nV ) std::cout << "No cycles";
        else std::cout << "Cycles";

    }

    void checkCycle_Undirected() {

        // The function checks whether the given non directional - graph has a cycle
        /*
            The main idea revolves around BFS Traversal 
            1. Perform normal BFS traversal
            2. Start with any vertex as source
            3. Visit the neighbour of the current vertex
            4. If the vertex is already visited, then it implies that there is another path by which  the BFS traversal has already visited this edge.
                So there is  a cycle

            Example :
                1 - 2
                |   |
                3 - 4

                In BFS(1) -> we visit 2 and 3
                in BFS(2) -> we visit 4 and 1
                            1 is the parent, we shouldnt take the edge to the parent as a cycle
                in BFS(3) -> we visit 4 and 1
                            Since 4 is already visited(through 1 - 2 - 4), ITS A CYCLE 
        */
        std::vector<int> Visited(nV, 0);
        std::queue<std::pair<int, int>> Q;
        // The algorithm is Very similar to BFS 
        /*
            Instead of Storing only the vertices the vertices in the Queue
            we need to store the node along with its parent to distinguishing
                Example :
                   1 - 2 - 3

                   adjacency list representation 
                   1 : 2 
                   2 : 1, 3
                   3 : 2

                   There is an edge from 1 to 2 also 2 to 1 cuz its an non directional graph
                    BUt we should not consider this as cycle

                So we should ignore 1(the parent of 2)
        */
        Q.push({0, -1});
        // 0 is the vertex -1 is the parent
        Visited[0] = 1;

        while ( !Q.empty() ) {
            int node = Q.front().first;
            int parent = Q.front().second;
            Q.pop();

            for ( int neighbour : List[node] ) {  // Iterate over the neighbours of the node
                if ( !Visited[neighbour] ) {
                    Visited[neighbour] = 1;      // If its not visited, add it to the queue
                    Q.push({neighbour, node});
                } else if ( neighbour != parent ) {        // IMPORATANT PART of the algorithm Explained above
                    std::cout << "Presence of Cycle";
                    return ;
                }
            }
        }
        std::cout << "No cycles";

    }

    void printAdjacencyList() {
        // Just a helper functiion to visualize the adjacency list

        for ( int i = 0 ; i < nV; i++ ) {
            std::cout <<  i+1 << ": ";
            for ( int j = 0 ; j < List[i].size(); j++ ) {
                std::cout << List[i][j] + 1<< ", ";
            }
            std::cout << "\n";
        }
    }    
};

int main () {
    Graph * graph = new Graph(6,4);
    graph->printAdjacencyList();
    graph->findShortestDistance(2 , 4);
    graph->findNumberOfComponents();
    graph->checkCycle();
    graph->checkCycle_Undirected();
    return 0;
} 
