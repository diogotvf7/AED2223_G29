//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_DATAMANAGER_H
#define AED2223_G29_DATAMANAGER_H

#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

#include "Airline.h"
#include "Airport.h"
#include "FlightGraph.h"
#include "City.h"
#include "Country.h"

typedef std::unordered_map<std::string, Airline*> UMairlines;
typedef std::unordered_map<std::string, Airport*> UMairports;
typedef std::unordered_map<std::string, City*> UMcities;
typedef std::unordered_map<std::string, Country*> UMcountries;

class DataManager {
    std::string path;
    UMairlines airlines;
    UMairports airports;
    UMcities cities;
    UMcountries countries;
    FlightGraph *fg;

    void readAirlines();
    void readAirports();
    void readFlights();
public:
    explicit DataManager(std::string path);
    UMairlines getAirlines() const;
    UMairports getAirports() const;
    FlightGraph *getFlightsGraph() const;
    UMcountries getCountries() const;
    UMcities getCities() const;

    FlightGraph createFlightGraph();
};


#endif //AED2223_G29_DATAMANAGER_H
