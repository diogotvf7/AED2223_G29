//
// Created by diogotvf7 on 03-01-2023.
//

#include "Country.h"

using namespace std;

Country::Country(string name) {
    this->name = name;
}

string Country::getName() const {
    return name;
}

list<Airport*> Country::getAirports() const {
    return airports;
}

list<Airline*> Country::getAirlines() const {
    return airlines;
}

void Country::addAirport(Airport *airport) {
    airports.push_back(airport);
}

void Country::addAirline(Airline *airline) {
    airlines.push_back(airline);
}
