//
// Created by diogotvf7 on 29-12-2022.
//
#include "FlightGraph.h"

FlightGraph::FlightGraph(airportsUM airports, airlinesUM airlines) {
    this->airports = airports;
    this->airlines = airlines;
}

void FlightGraph::addFlight(Airport *source, Airport *target, Airline *airline) {
    double distance = source->getCoordinate().distanceTo(target->getCoordinate());
    source->addFlight({target, airline, distance});
}

