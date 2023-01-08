//
// Created by diogotvf7 on 29-12-2022.
//
#include "FlightGraph.h"

using namespace std;

//
// Constructor:
//
FlightGraph::FlightGraph(UMairports &airports, UMairlines &airlines, UMcountries &countries, UMcities &cities) {
    this->airports = airports;
    this->airlines = airlines;
    this->countries = countries;
    this->cities = cities;
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
        Airport *ap = flight.getTarget();
        if (!ap->getToken())
            dfs(ap->getCode());
    }
}

void FlightGraph::listComponent(const string &airport, vector<string> &vairports, list<Airline*> filter) {
    airports[airport]->setToken(true);
    vairports.push_back(airport);
    for (Flight flight : airports[airport]->getFlights()) {
        Airport *ap = flight.getTarget();
        if (!filter.empty() && find(filter.begin(), filter.end(), flight.getAirline()) == filter.end()) continue;
        if (!ap->getToken())
            listComponent(ap->getCode(), vairports);
    }
}

void FlightGraph::articulationAirports(const string &airport, int &order, list<Airport*> &artAirports) {
    airports[airport]->setToken(true); airports[airport]->setNum(order); airports[airport]->setLow(order); order++;

    int children = 0;
    bool articulation = false;

    for (Flight flight : airports[airport]->getFlights()) {
        Airport *ap = flight.getTarget();
        if (!ap->getToken()) {
            children++;
            articulationAirports(ap->getCode(), order, artAirports);
            airports[airport]->setLow(min(airports[airport]->getLow(), ap->getLow()));
            if (ap->getLow() >= airports[airport]->getNum())
                articulation = true;
        }
        else
            airports[airport]->setLow(min(airports[airport]->getLow(), ap->getNum()));
    }

    if (airports[airport]->getNum() == 1 && children > 1 || airports[airport]->getNum() > 1 && articulation)
        artAirports.push_back(airports[airport]);
}

void FlightGraph::stronglyConnectedComponents(const string &airport, stack<Airport*> &s, int &order, list<list<Airport*>> &sccs) {
    airports[airport]->setToken(true); airports[airport]->setToken2(true);
    airports[airport]->setNum(order); airports[airport]->setLow(order);
    s.push(airports[airport]); order++;

    for (Flight flight : airports[airport]->getFlights()) {
        Airport *ap = flight.getTarget();
        if (!ap->getToken()) {
            stronglyConnectedComponents(ap->getCode(),s,order,sccs);
            airports[airport]->setLow(min(airports[airport]->getLow(), ap->getLow()));
        }
        else if (ap->getToken2())
            airports[airport]->setLow(min(airports[airport]->getLow(), ap->getNum()));
    }

    if (airports[airport]->getLow() == airports[airport]->getNum()) {
        list<Airport*> scc;
        do {
            scc.push_back(s.top());
            airports[s.top()->getCode()]->setToken2(false);
            s.pop();
        } while (scc.back()->getCode() != airport);
        sccs.push_back(scc);
    }
}

//
// Breadth-First Search:
//
void FlightGraph::countFlights(const string &source) {
    for (auto &[name, apt] : airports) {
        airports[name]->setToken(false);
        airports[name]->setDistance(-1);
        apt->setPrev(nullptr);
    }
    queue<Airport*> q;

    q.push(airports[source]);
    airports[source]->setToken(true);
    airports[source]->setDistance(0);

    while (!q.empty()) {
        Airport *tmp = q.front(); q.pop();
        for (Flight flight : tmp->getFlights()) {
            Airport *target = flight.getTarget();
            if (!target->getToken()) {
                target->setPrev(tmp);
                target->setToken(true);
                target->setDistance(tmp->getDistance() + 1);
                q.push(target);
            }
        }
    }
}

void FlightGraph::dijkstra(const string &source) {
    for (auto &[name, apt] : airports) {
        apt->setToken(false);
        apt->setDistance(40075.017);
        apt->setPrev(nullptr);
    }
    airports[source]->setToken(true);
    airports[source]->setDistance(0);

    priority_queue<Airport*, vector<Airport*>, AirportCompare> pq;
    pq.push(airports[source]);

     while (!pq.empty()) {
        Airport *tmp = pq.top(); pq.pop();

        for (Flight e : tmp->getFlights()) {
            Airport *dest = e.getTarget();
            if (dest->getDistance() > tmp->getDistance() + e.getDistance()) {
                dest->setPrev(tmp);
                dest->setDistance(tmp->getDistance() + e.getDistance());
                pq.push(dest);
            }
        }
    }
}

unordered_set<string> FlightGraph::bfsInNFlights(const string &source, int n, int mode) {
    for (auto &[name, apt] : airports) {
        apt->setToken(false);
        apt->setDistance(-1);
    }
    unordered_set<string> ret;
    queue<Airport*> q;

    q.push(airports[source]);
    airports[source]->setToken(true);
    airports[source]->setDistance(0);

    while (!q.empty()) {
        Airport *tmp = q.front(); q.pop();
        for (Flight flight : tmp->getFlights()) {
            Airport *target = flight.getTarget();
            if (!target->getToken() && (n == 0 || tmp->getDistance() + 1 <= n)) {
                if (mode == 0) ret.insert(target->getCode());
                if (mode == 1) ret.insert(target->getCountry());
                if (mode == 2) ret.insert(target->getCity());
                if (mode == 3) ret.insert(flight.getAirline()->getCode());
                target->setPrev(tmp);
                target->setToken(true);
                target->setDistance(tmp->getDistance() + 1);
                q.push(target);
            }
        }
    }
    return ret;
}

//
// Search call functions:
//
vector<string> FlightGraph::reachableAirports(const string &source, list<Airline*> filter) {
    vector<string> res;
    for (auto &[name, airport] : airports)
        airports[name]->setToken(false);
    listComponent(source, res, filter);
    return res;
}

unordered_set<string> FlightGraph::airportsInNFlights(const string &source, int n) {
    return bfsInNFlights(source, n, 0);
}

unordered_set<string> FlightGraph::countriesInNFlights(const string &source, int n) {
    return bfsInNFlights(source, n, 1);
}

unordered_set<string> FlightGraph::citiesInNFlights(const string &source, int n) {
    return bfsInNFlights(source, n, 2);
}

unordered_set<string> FlightGraph::airlinesInNFlights(const string &source, int n) {
    return bfsInNFlights(source, n, 3);
}

double FlightGraph::minDistanceCodeCode(const string &source, const string &target, bool mode) {
    if (mode)
        countFlights(source);
    else
        dijkstra(source);
    return airports[target]->getDistance();
}

pair<Airport*,Airport*> FlightGraph::minDistanceCoordinateCode(Coordinate source, const string &target, bool mode, double radius) {
    pair<double,pair<Airport*,Airport*>> minimum = {40075.017, {}};
    for (auto &[key1, airport1] : airports) {
        if (source.distanceTo(airport1->getCoordinate()) < radius) {
            double tmp = minDistanceCodeCode(airport1->getCode(), airports[target]->getCode(), mode);
            if (tmp < minimum.first && tmp != -1)
                minimum = {tmp, {airport1, airports[target]}};
        }
    }
    return minimum.second;
}

pair<Airport*,Airport*> FlightGraph::minDistanceCityCode(const string &source, const string &target, bool mode) {
    pair<double,pair<Airport*,Airport*>> minimum = {40075.017, {}};
    for (Airport *airport1 : cities[source]->getAirports()) {
        double tmp = minDistanceCodeCode(airport1->getCode(), airports[target]->getCode(), mode);
        if (tmp < minimum.first && tmp != -1)
            minimum = {tmp, {airport1, airports[target]}};
    }
    return minimum.second;
}

pair<Airport*,Airport*> FlightGraph::minDistanceCountryCode(const string &source, const string &target, bool mode) {
    pair<double,pair<Airport*,Airport*>> minimum = {40075.017, {}};
    for (Airport *airport1 : countries[source]->getAirports()) {
        double tmp = minDistanceCodeCode(airport1->getCode(), airports[target]->getCode(), mode);
        if (tmp < minimum.first && tmp != -1)
            minimum = {tmp, {airport1, airports[target]}};
    }
    return minimum.second;
}

pair<Airport*,Airport*> FlightGraph::minDistanceCodeCoordinate(const string &source, Coordinate target, bool mode, double radius) {
    pair<double,pair<Airport*,Airport*>> minimum = {40075.017, {}};
    for (auto &[key1, airport2] : airports) {
        if (target.distanceTo(airport2->getCoordinate()) < radius) {
            double tmp = minDistanceCodeCode(airports[source]->getCode(), airport2->getCode(), mode);
            if (tmp < minimum.first && tmp != -1)
                minimum = {tmp, {airports[source], airport2}};
        }
    }
    return minimum.second;
}

pair<Airport*,Airport*> FlightGraph::minDistanceCoordinateCoordinate(Coordinate source, Coordinate target, bool mode, double radius) {
    pair<double,pair<Airport*,Airport*>> minimum = {40075.017, {}};
    for (auto &[key1, airport1] : airports) {
        if (source.distanceTo(airport1->getCoordinate()) < radius) {
            for (auto &[key2, airport2] : airports) {
                if (target.distanceTo(airport2->getCoordinate()) < radius) {
                    double tmp = minDistanceCodeCode(airport1->getCode(), airport2->getCode(), mode);
                    if (tmp < minimum.first && tmp != -1)
                        minimum = {tmp, {airport1, airport2}};
                }
            }
        }
    }
    return minimum.second;
}

pair<Airport*,Airport*> FlightGraph::minDistanceCityCoordinate(const string &source, Coordinate target, bool mode, double radius) {
    pair<double,pair<Airport*,Airport*>> minimum = {40075.017, {}};
    for (Airport *airport1 : cities[source]->getAirports()) {
        for (auto &[key2, airport2] : airports) {
            if (target.distanceTo(airport2->getCoordinate()) < radius) {
                double tmp = minDistanceCodeCode(airport1->getCode(), airport2->getCode(), mode);
                if (tmp < minimum.first && tmp != -1)
                    minimum = {tmp, {airport1, airport2}};
            }
        }
    }
    return minimum.second;
}

pair<Airport*,Airport*> FlightGraph::minDistanceCountryCoordinate(const string &source, Coordinate target, bool mode, double radius) {
    pair<double,pair<Airport*,Airport*>> minimum = {40075.017, {}};
    for (Airport *airport1 : countries[source]->getAirports()) {
        for (auto &[key2, airport2] : airports) {
            if (target.distanceTo(airport2->getCoordinate()) < radius) {
                double tmp = minDistanceCodeCode(airport1->getCode(), airport2->getCode(), mode);
                if (tmp < minimum.first && tmp != -1)
                    minimum = {tmp, {airport1, airport2}};
            }
        }
    }
    return minimum.second;
}

pair<Airport*,Airport*> FlightGraph::minDistanceCodeCity(const string &source, const string &target, bool mode) {
    pair<double,pair<Airport*,Airport*>> minimum = {40075.017, {}};
    for (Airport *airport2 : cities[target]->getAirports()) {
        double tmp = minDistanceCodeCode(airports[source]->getCode(), airport2->getCode(), mode);
        if (tmp < minimum.first && tmp != -1)
            minimum = {tmp, {airports[source], airport2}};
    }
    return minimum.second;
}

pair<Airport*,Airport*> FlightGraph::minDistanceCoordinateCity(Coordinate source, const string &target, bool mode, double radius) {
    pair<double,pair<Airport*,Airport*>> minimum = {40075.017, {}};
    for (auto &[key2, airport1] : airports) {
        if (source.distanceTo(airport1->getCoordinate()) < radius) {
            for (Airport *airport2 : cities[target]->getAirports()) {
                double tmp = minDistanceCodeCode(airport1->getCode(), airport2->getCode(), mode);
                if (tmp < minimum.first && tmp != -1)
                    minimum = {tmp, {airport1, airport2}};
            }
        }
    }
    return minimum.second;
}

pair<Airport*,Airport*> FlightGraph::minDistanceCityCity(const string &source, const string &target, bool mode) {
    pair<double,pair<Airport*,Airport*>> minimum = {40075.017, {}};
    for (Airport *airport1 : cities[source]->getAirports()) {
        for (Airport *airport2 : cities[target]->getAirports()) {
            double tmp = minDistanceCodeCode(airport1->getCode(), airport2->getCode(), mode);
            if (tmp < minimum.first && tmp != -1)
                minimum = {tmp, {airport1, airport2}};
        }
    }
    return minimum.second;
}

pair<Airport*,Airport*> FlightGraph::minDistanceCountryCity(const string &source, const string &target, bool mode) {
    pair<double,pair<Airport*,Airport*>> minimum = {40075.017, {}};
    for (Airport *airport1 : countries[source]->getAirports()) {
        for (Airport *airport2 : cities[target]->getAirports()) {
            double tmp = minDistanceCodeCode(airport1->getCode(), airport2->getCode(), mode);
            if (tmp < minimum.first && tmp != -1)
                minimum = {tmp, {airport1, airport2}};
        }
    }
    return minimum.second;
}

pair<Airport*,Airport*> FlightGraph::minDistanceCodeCountry(const string &source, const string &target, bool mode) {
    pair<double,pair<Airport*,Airport*>> minimum = {40075.017, {}};
    for (Airport *airport2 : countries[target]->getAirports()) {
        double tmp = minDistanceCodeCode(airports[source]->getCode(), airport2->getCode(), mode);
        if (tmp < minimum.first && tmp != -1)
            minimum = {tmp, {airports[source], airport2}};
    }
    return minimum.second;
}

pair<Airport*,Airport*> FlightGraph::minDistanceCoordinateCountry(Coordinate source, const string &target, bool mode, double radius) {
    pair<double,pair<Airport*,Airport*>> minimum = {40075.017, {}};
    for (auto &[key2, airport1] : airports) {
        if (source.distanceTo(airport1->getCoordinate()) < radius) {
            for (Airport *airport2 : countries[target]->getAirports()) {
                double tmp = minDistanceCodeCode(airport1->getCode(), airport2->getCode(), mode);
                if (tmp < minimum.first && tmp != -1)
                    minimum = {tmp, {airport1, airport2}};
            }
        }
    }
    return minimum.second;
}

pair<Airport*,Airport*> FlightGraph::minDistanceCityCountry(const string &source, const string &target, bool mode) {
    pair<double,pair<Airport*,Airport*>> minimum = {40075.017, {}};
    for (Airport *airport1 : cities[source]->getAirports()) {
        for (Airport *airport2 : countries[target]->getAirports()) {
            double tmp = minDistanceCodeCode(airport1->getCode(), airport2->getCode(), mode);
            if (tmp < minimum.first && tmp != -1)
                minimum = {tmp, {airport1, airport2}};
        }
    }
    return minimum.second;
}

pair<Airport*,Airport*> FlightGraph::minDistanceCountryCountry(const string &source, const string &target, bool mode) {
    pair<double,pair<Airport*,Airport*>> minimum = {40075.017, {}};
    for (Airport *airport1 : countries[source]->getAirports()) {
        for (Airport *airport2 : countries[target]->getAirports()) {
            double tmp = minDistanceCodeCode(airport1->getCode(), airport2->getCode(), mode);
            if (tmp < minimum.first && tmp != -1)
                minimum = {tmp, {airport1, airport2}};
        }
    }
    return minimum.second;
}

list<Airport*> FlightGraph::getArticulationAirports() {
    for (auto &[key, airport] : airports) {
        airport->setToken(false);
        airport->setLow(0);
        airport->setNum(0);
    }

    int order = 1; list<Airport*> artAirports;
    for (auto &[key, airport] : airports) {
        articulationAirports(airport->getCode(), order, artAirports);
    }
    return artAirports;
}

list<list<Airport*>> FlightGraph::getStronglyConnectedComponents() {
    for (auto &[key, airport] : airports) {
        airport->setToken(false);
        airport->setToken2(false);
        airport->setLow(0);
        airport->setNum(0);
    }

    int order = 1;
    stack<Airport*> s; list<list<Airport*>> sccs;
    for (auto &[key, airport] : airports)
        if (!airport->getToken())
            stronglyConnectedComponents(airport->getCode(), s, order, sccs);

    return sccs;
}

list<Airport*> FlightGraph::path(Airport *source, Airport *target) {
    Airport *tmp = target;
    list<Airport*> ret;

    while (tmp != nullptr) {
        ret.push_front(tmp);
        tmp = tmp->getPrev();
    }
    return ret;
}






