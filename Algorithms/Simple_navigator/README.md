Part 1. Depth- and Breadth-first search
Implementation of the s21_graph library:

The library must be developed in C++ language of C++17 standard.
The library code must be located in the src folder in the develop branch.
When writing code it is necessary to follow the Google style.
Make it as a static library (s21_graph).
The library must be represented as a Graph class that stores information about the graph using an adjacency matrix. The dimensionality of the adjacency matrix should be set dynamically when initializing the graph (when loading it from a file).
The program must be built with Makefile which contains standard set of targets for GNU-programs: all, clean, test, s21_graph.
*Prepare full coverage of the Graph class methods with unit-tests.
The class Graph must contain at least the following public methods:


LoadGraphFromFile(string filename) — loading a graph from a file in the adjacency matrix format.

ExportGraphToDot(string filename)- exporting a graph to a dot file (see materials).



Implementation of the s21_graph_algorithms.h library:

The library must be developed in C++ language of C++17 standard.
The library code must be located in the src folder in the develop branch.
Make it as a static library (s21_graph_algorithms).
The library must be represented as a GraphAlgorithms class that stores the implementation of algorithms on graphs. The class GraphAlgorithms itself must not know anything about the internal representation of the graph from the class Graph. To interact with graph data, the class GraphAlgorithms can only use the public methods and properties provided by the Graph class.
Add to the Makefile s21_graph_algorithms target.
Prepare full coverage of the GraphAlgorithms class methods with unit-tests.
The class GraphAlgorithms must contain at least the following public methods:


DepthFirstSearch(Graph &graph, int start_vertex) — a non-recursive depth-first search in the graph from a given vertex. The function should return an array that contains the traversed vertices in the order they were traversed. When implementing this function, you must use the self-written data structure stack, which should be previously made as a separate static library.

BreadthFirstSearch(Graph &graph, int start_vertex) — breadth-first search in the graph from a given vertex. The function should return an array that contains the traversed vertices in the order they were traversed. When implementing this function, you must use the self-written data structure queue, which should be previously made as a separate static library.


It is necessary to adapt previously created self-written helper classes Stack and Queue (you can reuse your solution from the CPP2 project for this) and implement interfaces for them in C++. These classes must contain the following methods:


stack() — creating an empty stack;

queue() — creating an empty queue;

push(value) — adding an element to the stack/queue;

pop() — getting an element from the stack/queue followed by its removal from the stack/queue;

top() — getting an element from the stack without its removal from the stack;

front() — getting the first element from the queue without its removal from the queue;

back() — getting the last element from the queue without its removal from the queue.



In this and the following tasks, consider that the vertex numbers start from 1.

Part 2. Finding the shortest paths in a graph

Add two new methods to the GraphAlgorithms class:


GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2) — searching for the shortest path between two vertices in a graph using Dijkstra's algorithm. The function accepts as input the numbers of two vertices and returns a numerical result equal to the smallest distance between them.

GetShortestPathsBetweenAllVertices(Graph &graph) — searching for the shortest paths between all pairs of vertices in a graph using the Floyd-Warshall algorithm. As a result, the function returns the matrix of the shortest paths between all vertices of the graph.




Part 3. Finding the minimum spanning tree

Add a new method to the GraphAlgorithms class:


GetLeastSpanningTree(Graph &graph) — searching for the minimal spanning tree in a graph using Prim's algorithm. As a result, the function should return the adjacency matrix for the minimal spanning tree.




Part 4. Traveling salesman problem

Add a new method to the GraphAlgorithms class:


SolveTravelingSalesmanProblem(Graph &graph) — solving the traveling salesman's problem using the ant colony algorithm.
You need to find the shortest path that goes through all vertices of the graph at least once, followed by a return to the original vertex. As a result, the function should return the TsmResult structure described below:


struct TsmResult {
    int* vertices;    // an array with the route you are looking for (with the vertex traverse order). Instead of int* you can use std::vector<int>
    double distance;  // the length of this route
}




If it is impossible to solve the problem with a given graph, output an error.

Part 5. Console interface

You need to write the main program, which is a console application for testing the functionality of the implemented s21_graph and s21_graph_algorithms libraries.
The console interface must provide the following functionality:

Load the original graph from a file.
Traverse the graph in breadth and print the result to the console.
Traverse the graph in depth and print the result to the console.
Find the shortest path between any two vertices and print the result to the console.
Find the shortest paths between all pairs of vertices in the graph and print the result matrix to the console.
Search for the minimum spanning tree in the graph and print the resulting adjacency matrix to the console.
Solve the Salesman problem, with output of the resulting route and its length to the console.