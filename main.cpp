#include "graph.h"
#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc, char* argv[]) {
    // Error code for invalid input
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <from_city_code> <to_city_code>" << endl;
        return 1;
    }
    // Store command line input
    string from_city_code = argv[1];
    string to_city_code = argv[2];

    // Preparations for reading input files
    ifstream city_file("city.txt");
    ifstream road_file("road.txt");

    // Error code for being unable to open either file
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

        // Create new city object from data read in, add it to the graph
        City newCity = City(id, code, name, population, elevation);
        graph.addCity(newCity);
        //newCity.printCityInfo(); // Debugging: Print city info as it's added to the graph
    }

    // Boolean for checking valid input
    bool isValidInput = false;

    // Check if city code 1 from command line matches anything in the city list
    for (long unsigned int i = 0; i < graph.citiesList.size(); i++) {
        if (argv[1] == graph.citiesList[i].getCode()) {
            isValidInput = true;
            break;
        }        
    } 
    // Exit program if it doesn't, print error code
    if (!isValidInput) {
        cerr << "Invalid city code: " << argv[1] << endl;
        return 0;
    }

    isValidInput = false;

    // Check if city code 2 from command line matches anything in the city list
    for (long unsigned int i = 0; i < graph.citiesList.size(); i++) {
        if (argv[2] == graph.citiesList[i].getCode()) {
            isValidInput = true;
            break;
        }        
    } 

    // Exit program if it doesn't, print error code
    if (!isValidInput) {
        cerr << "Invalid city code: " << argv[2] << endl;
        return 0;
    }

    // Read road data
    // Road format from text file: from_city, to_city, distance
    while (getline(road_file, line)) {
    stringstream ss(line);
    string from_city_code, to_city_code;
    int distance;
    ss >> from_city_code >> to_city_code >> distance;

    // Find the indices of the cities with the given codes in the citiesList
    int from_city_index = -1;
    int to_city_index = -1;

    // Iterate through the list of cities added to the graph, and if the city's code matches the command line input code, update from/to_city_index variables
    for (int i = 0; i < graph.numCities; ++i) {
        if (graph.citiesList[i].getId() == from_city_code) {
            from_city_index = i;
        } else if (graph.citiesList[i].getId() == to_city_code) {
            to_city_index = i;
        }

        // Break out of the loop if both cities are found
        if (from_city_index != -1 && to_city_index != -1) {
            break;
        }
    }

    // Check if both cities were found
    if (from_city_index != -1 && to_city_index != -1) {
        // Add a directed road to the graph
        graph.addDirectedRoad(from_city_index, to_city_index, distance);
        // Road(from_city_index, to_city_index, distance).printRoadInfo(); // Debugging: print road info as it's added to the graph
    } else {
        cerr << "Error: City not found for road: " << from_city_code << " to " << to_city_code << endl;
    }
}

 // Need to go from abbreviation to ID number
 // Assuming the cities are added in the order of their indices
    int startCityIndex;
    int endCityIndex;

    // 
    for (int i = 0; i < graph.numCities; i++ ) {
        if (graph.citiesList[i].getCode() == from_city_code) {
            startCityIndex = i;
        } else if (graph.citiesList[i].getCode() == to_city_code) {
            endCityIndex = i;
        }
    }

    // If indices are valid, 
    if (startCityIndex != -1 && endCityIndex != -1) {
    // Calculate the shortest route between the two cities
    vector<int> shortestPath = graph.shortestRoute(startCityIndex, endCityIndex);
    // Store route length
    int weight_sum = 0;
    
    // For each city in the shortest path
    for (long unsigned int i = 0; i < shortestPath.size() - 1; i++) {
        // Shortestpath[i] returns city ID (first column)
        int currentIndex = shortestPath[i];
        int nextIndex = shortestPath[i + 1];

        for (const auto &road : graph.adjList[currentIndex]) {
            if (road.destination_city_index == nextIndex) {
                // Found the road that connects the current city to the next city
                // Add its weight to the total sum
                weight_sum += road.weight;
                break;
            }
        }
    }


    // output
    cout << "Author: Lucas Birkenstock, xxx and xxxx" << endl;
    cout << "Date: 12/08/2023" << endl;
    cout << "Course: CS311 (Data structures and Algorithms)" << endl;
    cout << "Description : Program to find the shortest route between cities" << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << "From City: " << graph.citiesList[startCityIndex].getName() << ", population " << graph.citiesList[startCityIndex].getPopulation() 
    << ", elevation " << graph.citiesList[startCityIndex].getElevation() << endl;
    cout << "To City: " << graph.citiesList[endCityIndex].getName() << ", population " << graph.citiesList[endCityIndex].getPopulation() 
    << ", elevation " << graph.citiesList[endCityIndex].getElevation() << endl << endl << endl;

    // If no path exists
    if (weight_sum == 0) {
        cout << "No route from " << graph.citiesList[startCityIndex].getName() << " to " << graph.citiesList[endCityIndex].getName() << endl;
        return 0;
    }
    // Print the shortest path
    cout << "Shortest Path from " << graph.citiesList[startCityIndex].getName() << " to " << graph.citiesList[endCityIndex].getName() << ": ";
    for (int cityIndex : shortestPath) {
        cout << graph.citiesList[cityIndex].getName() << " ";
    }
    cout << endl << "The shortest distance from " << graph.citiesList[startCityIndex].getName() << " to " << graph.citiesList[endCityIndex].getName() << " is: " << weight_sum;
    cout << endl;
} else {
    cerr << "Error: One or both cities not found." << endl;
}

   
    return 0;
}


