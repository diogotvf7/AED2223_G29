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
    /**
     * @brief Constructor for the Country class
     * @param name the Country's name
     */
    Country(std::string name);
    /**
     * @brief Get method for the name field
     * @return returns the value of the name field
     */
    [[nodiscard]] std::string getName() const;
    /**
     * @brief Get method for the Country's airports vector field
     * @return returns the Country's airports vector field
     */
    [[nodiscard]] std::vector<Airport*> getAirports() const;
    /**
     * @brief Get method for the Country's airlines vector field
     * @return returns the Country's airlines vector field
     */
    [[nodiscard]] std::vector<Airline*> getAirlines() const;
    /**
     * @brief Get method for the Country's Cities vector field
     * @return returns the Country's Cities vector field
     */
    [[nodiscard]] std::vector<City*> getCities() const;
    /**
     * @brief This function is used to add an Airport to the Airport pointers vector
     * @param airport the Airport pointer to be added
     */
    void addAirport(Airport *airport);
    /**
     * @brief This function is used to add an Airline to the Airline pointers vector
     * @param airline the Airline pointer to be added
     */
    void addAirline(Airline *airline);
    /**
     * @brief This function is used to add a City to the City pointers vector
     * @param city the City pointer to be added
     */
    void addCity(City *city);
};

#endif //AED2223_G29_COUNTRY_H
