//
// Created by diogotvf7 on 29-12-2022.
//
#include <vector>
#include <queue>
#include "FlightGraph.h"
#include "../MinMaxStack.hpp"

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
    airports[airport]->setToken(true);
    for (Flight flight : airports[airport]->getFlights()) {
        string ap = flight.getTarget()->getCode();
        if (!airports[ap]->getToken())
            dfs(ap);
    }
}

void FlightGraph::dfsList(string airport, vector<string> &vairports) {
    airports[airport]->setToken(true);
    vairports.push_back(airport);
    for (Flight flight : airports[airport]->getFlights()) {
        string ap = flight.getTarget()->getCode();
        if (!airports[ap]->getToken())
            dfsList(ap, vairports);
    }
}

//
// Breadth-First Search:
//
void FlightGraph::dijkstra(const string &source, bool mode) {
    for (auto &[name, airport] : airports) {
        airport->setToken(false);
        airport->setDistance(40075.017);
    }
    airports[source]->setToken(true);
    airports[source]->setDistance(0);

    priority_queue<Airport*, vector<Airport*>, AiportCompare> pq;
    pq.push(airports[source]);

     while (!pq.empty()) {
        Airport *u = pq.top(); pq.pop();

        for (Flight e : u->getFlights()) {
            Airport *v = e.getTarget();
            if (v->getDistance() > u->getDistance() + e.getDistance()) {
                v->setDistance(u->getDistance() + (mode ? 1 : e.getDistance()));
                pq.push(v);
            }
        }
    }
}

//
// Search call functions:
//
std::vector<std::string> FlightGraph::reachableAirports(string source) {
    vector<string> res;
    for (auto &[name, airport] : airports)
        airports[name]->setToken(false);
    dfsList(source, res);
    return res;
}

std::set<std::string> FlightGraph::reachableCities(std::string source) {
    return std::set<std::string>();
}

double FlightGraph::minDistance(std::string source, std::string target, bool mode) {
    dijkstra(source, mode);
    return airports[target]->getDistance();
}


