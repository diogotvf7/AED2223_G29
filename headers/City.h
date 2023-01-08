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
    /**
     * @brief Constructor for the City class
     * @param name the City's name
     */
    City(std::string name);
    /**
     * @brief Get method for the name field
     * @return returns the value of the name field
     */
    [[nodiscard]] std::string getName() const;
    /**
     * @brief Get method for the City's airports vector field
     * @return returns the City's airports vector field
     */
    [[nodiscard]] std::vector<Airport *> getAirports() const;
    /**
     * @brief This function is used to add an Airport to the Airport pointers vector
     * @param airport the Airport pointer to be added
     */
    void addAirport(Airport *airport);
};

#endif //AED2223_G29_CITY_H
