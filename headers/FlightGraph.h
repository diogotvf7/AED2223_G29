//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_FLIGHTGRAPH_H
#define AED2223_G29_FLIGHTGRAPH_H

#include <fstream>
#include <sstream>
#include <list>
#include <set>
#include <unordered_map>
#include <string>

#include "Airline.h"
#include "Airport.h"
#include "Flight.h"

class Airport;

typedef std::unordered_map<std::string, Airline*> UMairlines;
typedef std::unordered_map<std::string, Airport*> UMairports;
typedef std::unordered_map<std::string, bool> UMbool;

class FlightGraph {

    UMairlines airlines;
    UMairports airports;

public:
    // Constructor:
    FlightGraph(UMairports airports, UMairlines airlines);

    // Add flight to airport:
    void addFlight(Airport *source, Airport *target, Airline *airline);

    // Depth-First Search:
    void dfs(std::string airport, UMbool &isVisited);
    void dfsList(std::string airport, std::list<std::string> &lairports, UMbool &isVisited);

    // Breadth-First Search:
    void bfs(int v);
    void bfsDist(int a, int b);
    int bfsMaxDist(int v);

    // Search call functions:
    std::list<std::string> reachableAirports(std::string source);
    std::set<std::string> reachableCities(std::string source);

};

#endif //AED2223_G29_FLIGHTGRAPH_H
