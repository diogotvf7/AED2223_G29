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
typedef std::unordered_set<City*, CityHash, CityHash> UScities;
typedef std::unordered_set<Country*, CountryHash, CountryHash> UScountries;

class DataManager {
    std::string path;
    UMairlines airlines;
    UMairports airports;
    UScities cities;
    UScountries countries;
    FlightGraph *fg;

    void readAirlines();
    void readAirports();
    void readFlights();
public:
    explicit DataManager(std::string path);
    UMairlines getAirlines() const;
    UMairports getAirports() const;
    FlightGraph *getFlightsGraph() const;
    UScountries getCountries() const;
    UScities getCities() const;

    FlightGraph createFlightGraph();
};


#endif //AED2223_G29_DATAMANAGER_H
