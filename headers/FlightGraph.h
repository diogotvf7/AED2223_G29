//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_FLIGHTGRAPH_H
#define AED2223_G29_FLIGHTGRAPH_H

#include <fstream>
#include <sstream>
#include <string>

#include <unordered_map>
#include <list>

#include "Airline.h"
#include "Airport.h"
#include "Flight.h"

typedef std::unordered_map<std::string, Airline*> airlinesUM;
typedef std::unordered_map<std::string, Airport*> airportsUM;

class FlightGraph {

    airlinesUM airlines;
    airportsUM airports;

public:
    FlightGraph(airportsUM airports, airlinesUM airlines);

    void addFlight(Airport *source, Airport *target, Airline *airline);
};

#endif //AED2223_G29_FLIGHTGRAPH_H
