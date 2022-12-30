//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_AIRPORT_H
#define AED2223_G29_AIRPORT_H

#include <string>

#include "Coordinate.h"

class Airport {
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    Coordinate coordinate;

public:
    Airport(std::string code, std::string name, std::string city, std::string country, Coordinate coordinate);
    std::string getCode() const;
    std::string getName() const;
    std::string getCity() const;
    std::string getCountry() const;
    Coordinate getCoordinate() const;
};

struct AirportHash
{
    int operator() (const Airport *a) const {
        int hashValue = 0;
        for (char ch : a->getCode())
            hashValue += hashValue * 37 + ch;
        return hashValue;
    }

    bool operator() (const Airport *a1, const Airport *a2) const {
        return a1->getCode() == a2->getCode();
    }
};
#endif //AED2223_G29_AIRPORT_H
