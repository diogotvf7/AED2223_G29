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
    Airline(std::string code, std::string name, std::string callsign, std::string country);
    [[nodiscard]] const std::string &getCode() const;
    [[nodiscard]] const std::string &getName() const;
    [[nodiscard]] const std::string &getCallsign() const;
    [[nodiscard]] const std::string &getCountry() const;
};

#endif //AED2223_G29_AIRLINE_H
