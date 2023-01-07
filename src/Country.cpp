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

std::vector<Airport*> Country::getAirports() const {
    return airports;
}

std::vector<Airline*> Country::getAirlines() const {
    return airlines;
}

std::vector<City*> Country::getCities() const {
    return cities;
}

void Country::addAirport(Airport *airport) {
    airports.push_back(airport);
}

void Country::addAirline(Airline *airline) {
    airlines.push_back(airline);
}

void Country::addCity(City *city) {
    cities.push_back(city);
}
