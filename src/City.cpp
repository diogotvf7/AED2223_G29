//
// Created by diogotvf7 on 31-12-2022.
//

#include "City.h"

using namespace std;

City::City(string name) {
    this->name = name;
}

string City::getName() const {
    return name;
}

list<Airport*> City::getAirports() const {
    return airports;
}

void City::addAirport(Airport *airport) {
    airports.push_back(airport);
}

