//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_AIRPORT_H
#define AED2223_G29_AIRPORT_H

#include <list>
#include <string>

#include "Flight.h"
#include "Coordinate.h"
#include "FlightGraph.h"

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
    [[nodiscard]] std::string getCode() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getCity() const;
    [[nodiscard]] std::string getCountry() const;
    [[nodiscard]] Coordinate getCoordinate() const;
    [[nodiscard]] std::list<Flight> getFlights() const;

    void addFlight(Flight f);
};
#endif //AED2223_G29_AIRPORT_H
