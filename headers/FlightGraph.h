//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_FLIGHTGRAPH_H
#define AED2223_G29_FLIGHTGRAPH_H

#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <string>

#include "Airline.h"
#include "Airport.h"
#include "Flight.h"

class Airport;

typedef std::unordered_map<std::string, Airline*> UMairlines;
typedef std::unordered_map<std::string, Airport*> UMairports;

class FlightGraph {

    UMairlines airlines;
    UMairports airports;

public:
    // Constructor:
    FlightGraph(UMairports airports, UMairlines airlines);

    // Add flight to airport:
    void addFlight(Airport *source, Airport *target, Airline *airline);

    // Depth-First Search:
    void dfs(const std::string &airport);
    void listComponent(const std::string &airport, std::vector<std::string> &vairports);

    // Breadth-First Search:
    void countFlights(const std::string &source);
    void dijkstra(const std::string &source);
    std::unordered_set<std::string> bfsInNFlights(const std::string &source, int n, int mode);

    // Search call functions:
    std::vector<std::string> reachableAirports(const std::string &source);
    std::unordered_set<std::string> airportsInNFlights(const std::string &source, int n);
    std::unordered_set<std::string> countriesInNFlights(const std::string &source, int n);
    std::unordered_set<std::string> citiesInNFlights(const std::string &source, int n);
    std::unordered_set<std::string> airlinesInNFlights(const std::string &source, int n);
    double minDistance(const std::string &source, const std::string &target, bool mode);
    std::list<Airport*> path(Airport *source, Airport *target);

};

#endif //AED2223_G29_FLIGHTGRAPH_H
