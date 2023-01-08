//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_AIRLINE_H
#define AED2223_G29_AIRLINE_H

#include <string>

class Airline {
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;

public:
    /**
     * @brief Constructor for the Airline class
     * @param code the Airline's code
     * @param name the Airline's name
     * @param callsign the Airline's callsign
     * @param country the Airline's country
     */
    Airline(std::string code, std::string name, std::string callsign, std::string country);
    /**
     * @brief Get method for the code field
     * @return returns the value of the code field
     */
    [[nodiscard]] const std::string &getCode() const;
    /**
     * @brief Get method for the name field
     * @return returns the value of the name field
     */
    [[nodiscard]] const std::string &getName() const;
    /**
     * @brief Get method for the callsign field
     * @return returns the value of the callsign field
     */
    [[nodiscard]] const std::string &getCallsign() const;
    /**
     * @brief Get method for the country field
     * @return returns the value of the country field
     */
    [[nodiscard]] const std::string &getCountry() const;
};

#endif //AED2223_G29_AIRLINE_H
