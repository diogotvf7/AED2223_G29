//
// Created by diogotvf7 on 31-12-2022.
//

#ifndef AED2223_G29_CITY_H
#define AED2223_G29_CITY_H

#include <list>
#include <string>

#include "Airport.h"
#include "Airline.h"

class Airport;

class City {
    std::string name;
    std::vector<Airport*> airports;

public:
    City(std::string name);
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::vector<Airport *> getAirports() const;

    void addAirport(Airport *airport);
};

#endif //AED2223_G29_CITY_H
