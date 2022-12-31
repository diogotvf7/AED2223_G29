//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_FLIGHTGRAPH_H
#define AED2223_G29_FLIGHTGRAPH_H

#include <fstream>
#include <sstream>
#include <string>

#include <unordered_map>
#include <list>

#include "Airline.h"
#include "Airport.h"
#include "Flight.h"

class Airport;

typedef std::unordered_map<std::string, Airline*> UMairlines;
typedef std::unordered_map<std::string, Airport*> UMairports;
typedef std::list<std::list<Airport*>> LLairports;
typedef std::list<Airport*> Lairports;

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

    // Breadth-First Search:
    void bfs(int v);
    void bfsDist(int a, int b);
    int bfsMaxDist(int v);

    // Search call functions:
    LLairports connectedComponents();

};

#endif //AED2223_G29_FLIGHTGRAPH_H
