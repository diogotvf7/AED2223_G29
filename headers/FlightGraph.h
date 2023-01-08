//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_FLIGHTGRAPH_H
#define AED2223_G29_FLIGHTGRAPH_H

#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>

#include "Airline.h"
#include "Airport.h"
#include "Flight.h"
#include "City.h"
#include "Country.h"

class Airport;
class Country;
class City;

typedef std::unordered_map<std::string, Airline*> UMairlines;
typedef std::unordered_map<std::string, Airport*> UMairports;
typedef std::unordered_map<std::string, City*> UMcities;
typedef std::unordered_map<std::string, Country*> UMcountries;

class FlightGraph {
    UMairlines airlines;
    UMairports airports;
    UMcountries countries;
    UMcities cities;

public:
    // Constructor:
    FlightGraph(UMairports &airports, UMairlines &airlines, UMcountries &countries, UMcities &cities);

    // Add flight to airport:
    void addFlight(Airport *source, Airport *target, Airline *airline);

    // Depth-First Search:
    void dfs(const std::string &airport);
    void listComponent(const std::string &airport, std::vector<std::string> &vairports, std::list<Airline*> filter = {});
    void articulationAirports(const std::string &airport, int &order, std::list<Airport*> &artAirports);
    void stronglyConnectedComponents(const std::string &airport, std::stack<Airport*> &s, int &order, std::list<std::list<Airport*>> &sccs);

    // Breadth-First Search:
    void countFlights(const std::string &source);
    void dijkstra(const std::string &source);
    std::unordered_set<std::string> bfsInNFlights(const std::string &source, int n, int mode);

    // Search call functions:
    std::vector<std::string> reachableAirports(const std::string &source, std::list<Airline*> filter = {});
    std::unordered_set<std::string> airportsInNFlights(const std::string &source, int n);
    std::unordered_set<std::string> countriesInNFlights(const std::string &source, int n);
    std::unordered_set<std::string> citiesInNFlights(const std::string &source, int n);
    std::unordered_set<std::string> airlinesInNFlights(const std::string &source, int n);

    double minDistanceCodeCode(const std::string &source, const std::string &target, bool mode);
    std::pair<Airport*,Airport*> minDistanceCoordinateCode(Coordinate source, const std::string &target, bool mode, double radius);
    std::pair<Airport*,Airport*> minDistanceCityCode(const std::string &source, const std::string &target, bool mode);
    std::pair<Airport*,Airport*> minDistanceCountryCode(const std::string &source, const std::string &target, bool mode);
    std::pair<Airport*,Airport*> minDistanceCodeCoordinate(const std::string &source, Coordinate target, bool mode, double radius);
    std::pair<Airport*,Airport*> minDistanceCoordinateCoordinate(Coordinate source, Coordinate target, bool mode, double radius);
    std::pair<Airport*,Airport*> minDistanceCityCoordinate(const std::string &source, Coordinate target, bool mode, double radius);
    std::pair<Airport*,Airport*> minDistanceCountryCoordinate(const std::string &source, Coordinate target, bool mode, double radius);
    std::pair<Airport*,Airport*> minDistanceCodeCity(const std::string &source, const std::string &target, bool mode);
    std::pair<Airport*,Airport*> minDistanceCoordinateCity(Coordinate source, const std::string &target, bool mode, double radius);
    std::pair<Airport*,Airport*> minDistanceCityCity(const std::string &source, const std::string &target, bool mode);
    std::pair<Airport*,Airport*> minDistanceCountryCity(const std::string &source, const std::string &target, bool mode);
    std::pair<Airport*,Airport*> minDistanceCodeCountry(const std::string &source, const std::string &target, bool mode);
    std::pair<Airport*,Airport*> minDistanceCoordinateCountry(Coordinate source, const std::string &target, bool mode, double radius);
    std::pair<Airport*,Airport*> minDistanceCityCountry(const std::string &source, const std::string &target, bool mode);
    std::pair<Airport*,Airport*> minDistanceCountryCountry(const std::string &source, const std::string &target, bool mode);

    std::list<Airport*> getArticulationAirports();
    std::list<std::list<Airport*>> getStronglyConnectedComponents();

    std::list<Airport*> path(Airport *source, Airport *target);

};

#endif //AED2223_G29_FLIGHTGRAPH_H
