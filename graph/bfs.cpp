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
            Parent[i] = -2;          // Parent of each vertex is unknown
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

        std::vector<int> Visited(nE);

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
    Graph * graph = new Graph(8,10);
    // graph->printAdjacencyList();
    // graph->findShortestDistance(6, 5);
    graph->findNumberOfComponents();
    return 0;
}