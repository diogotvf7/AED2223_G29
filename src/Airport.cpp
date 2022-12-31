//
// Created by diogotvf7 on 29-12-2022.
//
#include "../headers/Airport.h"

using namespace std;

Airport::Airport(string code, string name, string city, string country, Coordinate coordinate) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->coordinate = coordinate;
    isVisited = false;
    distance = INFINITY;
}

string Airport::getCode() const {
    return code;
}

string Airport::getName() const {
    return name;
}

string Airport::getCity() const {
    return city;
}

string Airport::getCountry() const {
    return country;
}

Coordinate Airport::getCoordinate() const {
    return coordinate;
}

std::list<Flight> Airport::getFlights() const {
    return flights;
}

bool Airport::getState() const {
    return isVisited;
}

double Airport::getDistance() const {
    return distance;
}

void Airport::setState(bool state) {
    isVisited = state;
}

void Airport::setDistance(double dist) {
    distance = dist;
}

void Airport::addFlight(Flight f) {
    flights.push_back(f);
}



