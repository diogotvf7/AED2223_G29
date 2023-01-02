//
// Created by diogotvf7 on 29-12-2022.
//
#include <vector>
#include "FlightGraph.h"

using namespace std;

//
// Constructor:
//
FlightGraph::FlightGraph(UMairports airports, UMairlines airlines) {
    this->airports = airports;
    this->airlines = airlines;
}

//
// Add flight to airport:
//
void FlightGraph::addFlight(Airport *source, Airport *target, Airline *airline) {
    double distance = source->getCoordinate().distanceTo(target->getCoordinate());
    source->addFlight({target, airline, distance});
}

//
// Depth-First Search:
//
void FlightGraph::dfs(string airport, UMbool &isVisited) {
    isVisited[airport] = true;
    for (Flight flight : airports[airport]->getFlights()) {
        string ap = flight.getTarget()->getCode();
        if (!isVisited[ap])
            dfs(ap, isVisited);
    }
}

void FlightGraph::dfsList(string airport, list<string> &lairports, UMbool &isVisited) {
    isVisited[airport] = true;
    lairports.push_back(airport);
    for (Flight flight : airports[airport]->getFlights()) {
        string ap = flight.getTarget()->getCode();
        if (!isVisited[ap])
            dfsList(ap, lairports, isVisited);
    }
}

//
// Breadth-First Search:
//

//
// Search call functions:
//
list<string> FlightGraph::reachableAirports(string source) {
    list<string> res;
    UMbool isVisited;
    for (auto &[name, airport] : airports)
        isVisited[name] = false;
    dfsList(source, res, isVisited);
    return res;
}

std::set<std::string> FlightGraph::reachableCities(std::string source) {
    return std::set<std::string>();
}

