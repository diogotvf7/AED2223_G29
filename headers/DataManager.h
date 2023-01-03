//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_DATAMANAGER_H
#define AED2223_G29_DATAMANAGER_H

#include <fstream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>

#include "Airline.h"
#include "Airport.h"
#include "FlightGraph.h"

typedef std::unordered_map<std::string, Airline*> UMairlines;
typedef std::unordered_map<std::string, Airport*> UMairports;
typedef std::unordered_set<std::string> uss;

class DataManager {
    std::string path;
    UMairlines airlines;
    UMairports airports;
    uss cities, countries;


    void readAirlines();
    void readAirports();
public:
    DataManager(std::string path);
    UMairlines getAirlines() const;
    UMairports getAirports() const;
    uss getCities() const;
    uss getCountries() const;

    FlightGraph createFlightGraph();
};


#endif //AED2223_G29_DATAMANAGER_H
