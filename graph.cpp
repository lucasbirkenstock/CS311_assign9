#include "graph.h"
#include <stack>
#include <algorithm>
#include <queue>

// @brief Construct a Graph with the given number of vertices.
// @param nV The number of vertices in the graph.
Graph::Graph(int nV)
{
    // Set member var
    numCities = nV;
    // Vectors don't require  manual memory allocation and deallocation
    adjList.resize(nV);
    citiesList.resize(nV);
}

// @brief destructor
Graph::~Graph()
{
    // Don't need to do anything with vectors
}

// @brief add a vertex to the graph
void Graph::addCity(City c)
{
    // Add a vertex to the vertex vector
    citiesList.push_back(c);
    // Add an empty list to the adjacency list
    adjList.push_back(std::vector<Road>());
    // Increment the number of vertices
    numCities++;
}

// @brief add a directed edge v1->v2 to the graph
void Graph::addDirectedRoad(int v1, int v2, float weight)
{
    // Create a new edge in accordance with input
    Road directedRoad(v1, v2, weight);

    // Add this new edge to the adjacency list
    adjList[v1].push_back(directedRoad);
}

// @brief add an undirected edge to the graph
void Graph::addUndirectedRoad(int v1, int v2, float weight)
{
    // Same thing as other function, but both ways

    // Add edge v1->v2
    Road road1(v1, v2, weight);
    adjList[v1].push_back(road1);

    // Add edge v2->v1
    Road road2(v2, v1, weight);
    adjList[v2].push_back(road2);
}

// @brief the number of outgoing edges from a vertex
int Graph::outDegree(int v)
{
    // Simply return the size of a vertex's adjacency list
    return adjList[v].size();
}


// @brief depth first search from vertex v
vector<int> Graph::DepthFirstSearch(int v) {
    // Store list denoting visited nodes
    std::vector<bool> visited(numCities, false);
    // Return vector
    std::vector<int> result;
    // Stack for implementing algorithm
    std::stack<int> stack;

    // Push vertex onto the stack
    stack.push(v);

    // While the stack isn't empty:
    while (!stack.empty()) {
        // Examine the first node popped off the stack
        int currentCity = stack.top();
        stack.pop();

        // If this particular popped node isn't visited,
        if (!visited[currentCity]) {
            // Mark it as visited
            visited[currentCity] = true;
            // Add it to the result list
            result.push_back(currentCity);

            // Sort the neighbors before pushing them onto the stack (fixes autograder problem)
            // Make a new vector to store all neighbors of a current vertex, then use std::sort with ascending order.
            std::vector<int> neighbors;
            for (const Road& road : adjList[currentCity]) {
                int neighbor = road.destination_city_index;
                if (!visited[neighbor]) {
                    neighbors.push_back(neighbor);
                }
            }
            std::sort(neighbors.begin(), neighbors.end(), std::greater<int>());
            
            // Push the sorted neighbors onto the stack
            for (int neighbor : neighbors) {
                stack.push(neighbor);
            }
        }
    }
    // Return result
    return result;
}

// @brief breadth first search from a vertex
std::vector<int> Graph::BreadthFirstSearch(int v) {
    // Store visited vertices list
    std::vector<bool> visited(numCities, false);
    // Return vector
    std::vector<int> result;
    // Queue for algorithm
    std::queue<int> queue;

    // Mark vertex as visited
    visited[v] = true;
    // Add vertex to the queue
    queue.push(v);

    // While there is a vertex in the queue, 
    while (!queue.empty()) {
        // Examine the vertex at the front, remove it from the queue
        int currentCity = queue.front();
        queue.pop();

        // Add examined vertex to the result list
        result.push_back(currentCity);

        // For each edge in the adjacency list of the currently examined vertex,
        for (const Road& road : adjList[currentCity]) {
            // Store the index of an adjacent vertex as "neighbor"
            int neighbor = road.destination_city_index;
            // If this vertex was not visited, mark it visited, and add it to the queue
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.push(neighbor);
            }
        }
    }

    // Return output
    return result;
}


/**
 * @brief Check if the graph has cycles
 * @return true if the graph has cycles
 */
bool Graph::checkCycle()
{
    vector<bool> visited(numCities, false);
    //iterate through all vertices
    for (int i = 0; i < numCities; ++i) {
        //if vertex is not visited and dfsCheckCycle return true, a cycle is found
        if (!visited[i] && dfsCheckCycle(i, visited, -1)) {  //, adjList
            return true;
        }
    }

    return false; //no cycle detected
}

/**
 * @brief Utility function for DFS traversal to detect a cycle
 * @param v The current vertex being visited
 * @param visited A reference to a vector that tracks visited vertices
 * @param parent The parent vertex of the current vertex
 * @return true if a cycle is detected, false otherwise
 */
bool Graph::dfsCheckCycle(int v, vector<bool>& visited, int parent) 
{
    visited[v] = true;
    //iterate through all adjacent vertices
    for (const auto& road : adjList[v]) {
        int u = road.destination_city_index; //adjacent vertex

        if (!visited[u]) {
            //recursively call dfsCheckCycle on unvisited vertex
            if (dfsCheckCycle(u, visited, v)) { 
                return true;
            }
        } else if (u != parent) {
            //if adjacent vertex is visited and not parent, cycle detected
            return true;
        }
    }
    
    return false; //no cycle detected

}

/**
 * @brief Function to find the shortest route between two cities
 * @param startCityIndex The index of the starting city
 * @param endCityIndex The index of the destination city
 * @return A vector containing the indices of the cities along the shortest route
 */
vector<int> Graph::shortestRoute(int startCityIndex, int endCityIndex)
{
    //priority queue to store vertices that are being preprocessed
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > >pq;
    //create a vector for distances and initialize all distances as infinite (INT_MAX)
    vector<int> dist(numCities, INT_MAX);
    //vector to store shortest path tree
    vector<int> prev(numCities, -1);

    pq.push(make_pair(0, startCityIndex));
    dist[startCityIndex] = 0;

    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        //'u' is finalized, now consider all adjacent vertices of 'u'
        for (const auto& road:adjList[u]) {
            int v = road.destination_city_index;
            int weight = road.weight;

            //if there is a shorter path to 'v' through 'u'
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    //reconstruct the shortest path from endCityIndex to startCityIndex
    vector<int> path;
    for (int at = endCityIndex; at != -1; at = prev[at]) {
        path.push_back(at);
    }

    reverse(path.begin(), path.end());

    //if path contains only the startCityIndex, no path was found
    if (path.size() == 1 && path[0] == startCityIndex) {
        //no path found
        path.clear();
    }

    return path;
}

// @brief print the graph
void Graph::printGraph()
{
    cout << "Graph:" << endl;
    for (int i = 0; i < numCities; i++)
    {
        cout << i << ": ";
        for(auto j = adjList[i].begin(); j != adjList[i].end(); ++j)
        {
            cout << (*j).destination_city_index << " " ;
        }
        cout << endl;
    }
    cout << endl;
}

