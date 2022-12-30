//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_DATAMANAGER_H
#define AED2223_G29_DATAMANAGER_H

#include <fstream>
#include <sstream>
#include <unordered_set>

#include "Airline.h"
#include "Airport.h"

typedef std::unordered_set<Airline*, AirlineHash, AirlineHash> airlinesHT;
typedef std::unordered_set<Airport*, AirportHash, AirportHash> airportsHT;

class DataManager {
    airlinesHT airlines;
    airportsHT airports;

public:
    airlinesHT getAirlines() const;
    airportsHT getAirports() const;
    int readAirlines();
    int readAirports();
};


#endif //AED2223_G29_DATAMANAGER_H
