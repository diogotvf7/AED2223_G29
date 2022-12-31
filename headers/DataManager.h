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

class DataManager {
    UMairlines airlines;
    UMairports airports;

public:
    UMairlines getAirlines() const;
    UMairports getAirports() const;
    int readAirlines();
    int readAirports();

    FlightGraph createFlightGraph();
};


#endif //AED2223_G29_DATAMANAGER_H
