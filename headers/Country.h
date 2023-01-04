//
// Created by diogotvf7 on 03-01-2023.
//

#ifndef AED2223_G29_COUNTRY_H
#define AED2223_G29_COUNTRY_H

#include <list>
#include <string>

#include "Airport.h"
#include "Airline.h"

class Country {
    std::string name;
    std::list<Airport*> airports;
    std::list<Airline*> airlines;

public:
    Country(std::string name);
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::list<Airport*> getAirports() const;
    [[nodiscard]] std::list<Airline*> getAirlines() const;

    void addAirport(Airport *airport);
    void addAirline(Airline *airline);
};

struct CountryHash {
    int operator() (const Country *c) const {
        int hashValue = 0;
        for (auto ch : c->getName()) {
            hashValue = hashValue * 37 + ch;
        }
        return hashValue;
    }

    bool operator() (const Country *c1, const Country *c2) const {
        return c1->getName() == c2->getName();
    }
};

#endif //AED2223_G29_COUNTRY_H
