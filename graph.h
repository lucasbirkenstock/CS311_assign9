//CS311 graph.h
//INSTRUCTION:
//undirected graph class - header file template
//You must complete the  parts and then complete graph.cpp. Delete "" after you are done.
//You should always add comments to each function to describe its PURPOSE and PARAMETERS
#pragma once
#include <vector>
#include <list>
#include <queue>
#include <iostream>
using namespace std;

/**
 * @brief Vertex class
 * 
 */
class Vertex {
public:
    // The index of the vertex. starting from 0
    int id;
    // The name of the vertex. Additional attributes can be added
    string name;

    Vertex(int id = 0, string name="") {
        this->id = id;
        this->name = name;
    }
};

/**
 * @brief Edge class. It represents an edge from one vertex to another
 * 
 */
struct Edge {
    int from_vertex; // The index of the vertex where the edge starts
    int to_vertex; // index of the vertex where the edge ends.
    float weight; // The weight of the edge. Additional attributes can be added

    Edge(int from_vertex = 0, int to_vertex = 0, float weight = 0) {
        this->from_vertex = from_vertex;
        this->to_vertex = to_vertex;
        this->weight = weight;
    }
};

/**
 * @brief Graph class
 *
 */
class Graph
{
public:
    int numVerts;    // No. of vertices
    vector<Vertex> vertices; // The list of vertices
    vector<vector<Edge>> adjList; // The adjacency list

    // Default constructor. Create an empty graph
    Graph() {
        numVerts = 0;
    }

    // Constructor. Create a graph with n vertices
    Graph(int n);

    // Destructor
    ~Graph();


    /**
     * @brief Add a vertex to the graph
     * @param v The vertex to be added
     */
    void addVertex(Vertex v);

    /**
     * @brief Add a directed edge from v1 to v2 to the graph
     *
     * @param v1 The index of the vertex where the edge starts
     * @param v2 The index of the vertex where the edge ends
     * @param weight The weight of the edge
     */
    void addDirectedEdge(int v1, int v2, float weight = 1.0f);

    /**
     * @brief Add an undirected edge to the graph. An undirected edge is represented by two directed edges.
     * @param v1 The index of the first vertex
     * @param v2 The index of the second vertex
     */
     void addUndirectedEdge(int v1, int v2, float weight = 1.0f);

    /**
     * @brief the number of outgoing edges from vertex v
     * @param v The index of the vertex
     * @return The number of outgoing edges from the vertex
     */
    int outDegree(int v);

    /**
     * @brief Depth first search
     *
     * @param v The index of the vertex where the search starts
     * @return The list of vertices in the order they are visited
     */
    vector<int> DepthFirstSearch(int v);

    /**
     * @brief Breadth first search
     *
     * @param v The index of the vertex where the search starts
     * @return The list of vertices in the order they are visited
     */
    vector<int> BreadthFirstSearch(int v);

    /**
     * @brief Check if the undirected graph contains cycles
     * @return true if the graph has cycles
     */
    bool checkCycle();

    /**
      * @brief Print the graph
      */
    void printGraph();

};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <from_city_code> <to_city_code>" << endl;
        return 1;
    }

    string from_city_code = argv[1];
    string to_city_code = argv[2];

    ifstream city_file("city.txt");
    ifstream road_file("road.txt");

    if (!city_file || !road_file) {
        cerr << "Error: Unable to open data files." << endl;
        return 1;
    }

    Graph graph;

    // Read city data
    string line;
    while (getline(city_file, line)) {
        stringstream ss(line);
        string id, code, name;
        int population, elevation;
        ss >> id >> code >> name >> population >> elevation;
        City city(id, code, name, population, elevation);
        graph.addCity(city);
    }

    // Read road data
    while (getline(road_file, line)) {
        stringstream ss(line);
        string from, to;
        int distance;
        ss >> from >> to >> distance;
        Road road(from, to, distance);
        graph.addRoad(road);
    }

    // Find the shortest route
    int shortest_distance = graph.shortestRoute(from_city_code, to_city_code);

    // Print results
    cout << "Author: xxx, xxx and xxxx" << endl;
    cout << "Date: xx/xx/20xx" << endl;
    cout << "Course: CS311 (Data structures and Algorithms)" << endl;
    cout << "Description: Program to find the shortest route between cities" << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << "From City: " << graph.cities[from_city_code].City_Name << ", population "
         << graph.cities[from_city_code].Population << ", elevation " << graph.cities[from_city_code].Elevation << endl;
    cout << "To City: " << graph.cities[to_city_code].City_Name << ", population "
         << graph.cities[to_city_code].Population << ", elevation " << graph.cities[to_city_code].Elevation << endl;

    if (shortest_distance == numeric_limits<int>::max()) {
        cout << "No route from " << graph.cities[from_city_code].City_Name << " to "
             << graph.cities[to_city_code].City_Name << endl;
    } else {
        cout << "The shortest distance from " << graph.cities[from_city_code].City_Name << " to "
             << graph.cities[to_city_code].City_Name << " is " << shortest_distance << endl;
        cout << "through the route: "; // print the route here
    }

    return 0;
}
