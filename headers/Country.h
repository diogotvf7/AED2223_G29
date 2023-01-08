//
// Created by diogotvf7 on 03-01-2023.
//

#ifndef AED2223_G29_COUNTRY_H
#define AED2223_G29_COUNTRY_H

#include <vector>
#include <string>

#include "Airport.h"
#include "Airline.h"
#include "City.h"

class City;

class Country {
    std::string name;
    std::vector<Airport*> airports;
    std::vector<Airline*> airlines;
    std::vector<City*> cities;

public:
    Country(std::string name);
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::vector<Airport*> getAirports() const;
    [[nodiscard]] std::vector<Airline*> getAirlines() const;
    [[nodiscard]] std::vector<City*> getCities() const;

    void addAirport(Airport *airport);
    void addAirline(Airline *airline);
    void addCity(City *city);
};

#endif //AED2223_G29_COUNTRY_H
