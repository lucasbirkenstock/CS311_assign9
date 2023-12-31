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

class City {
    private: 
    // Member variables
    std::string mId, mCode, mName;
    int mPopulation, mElevation;

    public: 
    // Default constructor
    City() : mId(""), mCode(""), mName(""), mPopulation(0), mElevation(0){}
    // Constructor
    City(std::string id, std::string code, std::string name, int population, int elevation) {
        mId = id;
        mCode = code;
        mName = name;
        mPopulation = population;
        mElevation = elevation;
    }

    void printCityInfo() {
        cout << "City ID: " << mId << "\n"
           << "City Code: " << mCode << "\n"
           << "City Name: " << mName << "\n"
           << "Population: " << mPopulation << "\n"
           << "Elevation: " << mElevation << "\n"; 
    }

     // Getter methods
    std::string getId() const {
        return mId;
    }

    std::string getCode() const {
        return mCode;
    }

    std::string getName() const {
        return mName;
    }

    int getPopulation() const {
        return mPopulation;
    }

    int getElevation() const {
        return mElevation;
    }
};

struct Road {
    int origin_city_index; // The index of the vertex where the edge starts
    int destination_city_index; // index of the vertex where the edge ends.
    float weight; // The weight of the edge. Additional attributes can be added

    // Constructor
    Road(int from_city = 0, int to_city = 0, float weight = 0) {
        this->origin_city_index = from_city;
        this->destination_city_index = to_city;
        this->weight = weight;
    }

    void printRoadInfo() {
        cout << "Road from index " << origin_city_index << " to index " << destination_city_index << " with distance " << weight << endl;
    }
};


/**
 * @brief Graph class
 *
 */
class Graph
{
public:
    int numCities;    // No. of vertices
    vector<City> citiesList; // The list of vertices
    vector<vector<Road>> adjList; // The adjacency list

    // Default constructor. Create an empty graph
    Graph() {
        numCities = 0;
    }

    // Constructor. Create a graph with n vertices
    Graph(int n);

    // Destructor
    ~Graph();


    /**
     * @brief Add a vertex to the graph
     * @param v The vertex to be added
     */
    void addCity(City c);

    /**
     * @brief Add a directed edge from v1 to v2 to the graph
     *
     * @param v1 The index of the vertex where the edge starts
     * @param v2 The index of the vertex where the edge ends
     * @param weight The weight of the edge
     */
    void addDirectedRoad(int v1, int v2, float weight = 1.0f);

    /**
     * @brief Add an undirected edge to the graph. An undirected edge is represented by two directed edges.
     * @param v1 The index of the first vertex
     * @param v2 The index of the second vertex
     */
     void addUndirectedRoad(int v1, int v2, float weight = 1.0f);

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

    /**
     * @brief Find the shortest route between two cities in a weighted graph
     * @param startCityIndex The index of the starting city in the graph
     * @param endCityIndex The index of the destination city in the graph
     * @return A vector containing the indices of the cities along the shortest route, or an empty vector if no route exists
     */
    vector<int> shortestRoute(int startCityIndex, int endCityIndex);

    /**
     * @brief Perform a Depth-First Search (DFS) to detect cycles in an undirected graph
     * @param v The current vertex being visited
     * @param visited A reference to a vector that tracks visited vertices
     * @param parent The index of the parent vertex of the current vertex
     * @return true if a cycle is detected, false otherwise
     */
    bool dfsCheckCycle(int v, vector<bool>& visited, int parent);

    int getCityIndex(const Graph& graph, const string& cityCode);

};



