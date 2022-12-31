//
// Created by diogotvf7 on 31-12-2022.
//

#ifndef AED2223_G29_CITY_H
#define AED2223_G29_CITY_H

#include <list>
#include <string>

#include "Airport.h"
#include "Airline.h"

class City {
    std::string name;
    std::list<Airport> airports;
    std::list<Airline> airlines;

public:
    std::string getName() const;
    std::list<Airport> getAirports() const;
    std::list<Airline> getAirlines() const;
};


#endif //AED2223_G29_CITY_H
