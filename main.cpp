#include "graph.h"
#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

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
        City newCity = City(id, code, name, population, elevation);
        graph.addCity(newCity);
        //newCity.printCityInfo(); // Debugging: Print city info as it's added to the graph
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

    // // Find the shortest route
    // int shortest_distance = graph.shortestRoute(from_city_code, to_city_code);

    // // Print results
    // cout << "Author: xxx, xxx and xxxx" << endl;
    // cout << "Date: xx/xx/20xx" << endl;
    // cout << "Course: CS311 (Data structures and Algorithms)" << endl;
    // cout << "Description: Program to find the shortest route between cities" << endl;
    // cout << "----------------------------------------------------------------" << endl;
    // cout << "From City: " << graph.cities[from_city_code].City_Name << ", population "
    //      << graph.cities[from_city_code].Population << ", elevation " << graph.cities[from_city_code].Elevation << endl;
    // cout << "To City: " << graph.cities[to_city_code].City_Name << ", population "
    //      << graph.cities[to_city_code].Population << ", elevation " << graph.cities[to_city_code].Elevation << endl;

    // if (shortest_distance == numeric_limits<int>::max()) {
    //     cout << "No route from " << graph.cities[from_city_code].City_Name << " to "
    //          << graph.cities[to_city_code].City_Name << endl;
    // } else {
    //     cout << "The shortest distance from " << graph.cities[from_city_code].City_Name << " to "
    //          << graph.cities[to_city_code].City_Name << " is " << shortest_distance << endl;
    //     cout << "through the route: "; // print the route here
    // }

    return 0;
}


