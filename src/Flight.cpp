//
// Created by diogotvf7 on 29-12-2022.
//
#include "Flight.h"

Flight::Flight(Airport *target, Airline *airline, double distance) {
    this->target = target;
    this->airline = airline;
    this->distance = distance;
}

Airport *Flight::getTarget() const {
    return target;
}

Airline *Flight::getAirline() const {
    return airline;
}

double Flight::getDistance() const {
    return distance;
}

