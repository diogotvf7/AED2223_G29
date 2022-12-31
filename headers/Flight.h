//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_FLIGHT_H
#define AED2223_G29_FLIGHT_H

#include "Airport.h"
#include "Airline.h"

class Airport;

class Flight {
    Airport *target;
    Airline *airline;
    double distance;

public:
    Flight(Airport *target, Airline *airline, double distance);
    Airport *getTarget() const;
    Airline *getAirline() const;
    double getDistance() const;
};

#endif //AED2223_G29_FLIGHT_H
