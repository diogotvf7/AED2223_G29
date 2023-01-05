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
void FlightGraph::dfs(const string &airport) {
    airports[airport]->setToken(true);
    for (Flight flight : airports[airport]->getFlights()) {
        string ap = flight.getTarget()->getCode();
        if (!airports[ap]->getToken())
            dfs(ap);
    }
}

void FlightGraph::listComponent(const string &airport, vector<string> &vairports) {
    airports[airport]->setToken(true);
    vairports.push_back(airport);
    for (Flight flight : airports[airport]->getFlights()) {
        string ap = flight.getTarget()->getCode();
        if (!airports[ap]->getToken())
            listComponent(ap, vairports);
    }
}

//
// Breadth-First Search:
//
void FlightGraph::countFlights(const string &airport) {
    for (auto &[name, apt] : airports) {
        airports[name]->setToken(false);
        airports[name]->setDistance(-1);
        apt->setPrev(nullptr);
    }
    queue<Airport*> q;

    q.push(airports[airport]);
    airports[airport]->setToken(true);
    airports[airport]->setDistance(0);

    while (!q.empty()) {
        Airport *source = q.front(); q.pop();
        for (Flight flight : source->getFlights()) {
            Airport *target = flight.getTarget();
            if (!target->getToken()) {
                target->setPrev(source);
                target->setToken(true);
                target->setDistance(source->getDistance() + 1);
                q.push(target);
            }
        }
    }
}

void FlightGraph::dijkstra(const string &airport) {
    for (auto &[name, apt] : airports) {
        apt->setToken(false);
        apt->setDistance(40075.017);
        apt->setPrev(nullptr);
    }
    airports[airport]->setToken(true);
    airports[airport]->setDistance(0);

    priority_queue<Airport*, vector<Airport*>, AirportCompare> pq;
    pq.push(airports[airport]);

     while (!pq.empty()) {
        Airport *source = pq.top(); pq.pop();

        for (Flight e : source->getFlights()) {
            Airport *dest = e.getTarget();
            if (dest->getDistance() > source->getDistance() + e.getDistance()) {
                dest->setPrev(source);
                dest->setDistance(source->getDistance() +  e.getDistance());
                pq.push(dest);
            }
        }
    }
}

//
// Search call functions:
//
std::vector<std::string> FlightGraph::reachableAirports(const string &source) {
    vector<string> res;
    for (auto &[name, airport] : airports)
        airports[name]->setToken(false);
    listComponent(source, res);
    return res;
}

std::set<std::string> FlightGraph::reachableCities(const std::string &source) {
    return std::set<std::string>();
}

double FlightGraph::minDistance(const std::string &source, const std::string &target, bool mode) {
    if (mode)
        countFlights(source);
    else
        dijkstra(source);

    return airports[target]->getDistance();
}

std::list<Airport *> FlightGraph::path(Airport *source, Airport *target) {
    Airport *tmp = target;
    std::list<Airport*> ret;
    while (tmp->getPrev() != source) {
        ret.push_front(tmp);
        tmp = tmp->getPrev();
    }
    return ret;
}



