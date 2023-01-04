//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_FLIGHTGRAPH_H
#define AED2223_G29_FLIGHTGRAPH_H

#include <fstream>
#include <sstream>
#include <vector>
#include <set>
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
    void dfs(std::string airport);
    void dfsList(std::string airport, std::vector<std::string> &vairports);

    // Breadth-First Search:
    void dijkstra(const std::string &source, bool mode = false);

    // Search call functions:
    std::vector<std::string> reachableAirports(std::string source);
    std::set<std::string> reachableCities(std::string source);
    double minDistance(std::string source, std::string target, bool mode = false);

};

#endif //AED2223_G29_FLIGHTGRAPH_H
