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
    const std::string &getCode() const;
    const std::string &getName() const;
    const std::string &getCallsign() const;
    const std::string &getCountry() const;
};

struct AirlineHash
{
    int operator() (const Airline *al) const {
        int hashValue = 0;
        for (char ch : al->getCode())
            hashValue += hashValue * 37 + ch;
        return hashValue;
    }

    bool operator() (const Airline *al1, const Airline *al2) const {
        return al1->getCode() == al2->getCode();
    }
};

#endif //AED2223_G29_AIRLINE_H
