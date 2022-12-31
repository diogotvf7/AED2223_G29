//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_AIRPORT_H
#define AED2223_G29_AIRPORT_H

#include <list>
#include <string>

#include "Flight.h"
#include "Coordinate.h"

class Flight;

class Airport {
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    Coordinate coordinate;
    std::list<Flight> flights;

public:
    Airport(std::string code, std::string name, std::string city, std::string country, Coordinate coordinate);
    std::string getCode() const;
    std::string getName() const;
    std::string getCity() const;
    std::string getCountry() const;
    Coordinate getCoordinate() const;
    std::list<Flight> getFlights() const;

    void addFlight(Flight f);
};
#endif //AED2223_G29_AIRPORT_H
