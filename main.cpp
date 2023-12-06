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
        newCity.printCityInfo();
    }

    // // Read road data
    // while (getline(road_file, line)) {
    //     stringstream ss(line);
    //     string from, to;
    //     int distance;
    //     ss >> from >> to >> distance;
    //     Road road(from, to, distance);
    //     graph.addDirectedRoad(road);
    // }

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


