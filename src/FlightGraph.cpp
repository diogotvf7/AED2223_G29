//
// Created by diogotvf7 on 29-12-2022.
//
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
void FlightGraph::dfs(string airport) {
    airports[airport]->setState(true);
    for (Flight flight : airports[airport]->getFlights()) {
        string ap = flight.getTarget()->getCode();
        if (!airports[ap]->getState())
            dfs(ap);
    }
}

//
// Breadth-First Search:
//

//
// Search call functions:
//
LLairports FlightGraph::connectedComponents() {
    LLairports res;
    Lairports tmp;

    for (auto &[name, airport] : airports)
        airport->setState(false);

    for (auto &[name, airport] : airports) {
        if (!airports[name]->getState()) {
            if (!tmp.empty())
                res.push_back(tmp);
            tmp = {};
            dfs(name);
        }
        tmp.push_back(airport);
    }
    return res;
}

