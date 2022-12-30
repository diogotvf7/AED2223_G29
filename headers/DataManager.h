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

typedef std::unordered_map<std::string, Airline*> airlinesUM;
typedef std::unordered_map<std::string, Airport*> airportsUM;

class DataManager {
    airlinesUM airlines;
    airportsUM airports;

public:
    airlinesUM getAirlines() const;
    airportsUM getAirports() const;
    int readAirlines();
    int readAirports();
};


#endif //AED2223_G29_DATAMANAGER_H
