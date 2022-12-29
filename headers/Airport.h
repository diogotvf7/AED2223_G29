//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_AIRPORT_H
#define AED2223_G29_AIRPORT_H

#include <string>

class Airport {
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    float latitude;
    float longitude;

public:
    Airport(std::string code, std::string name, std::string city, std::string country, float latitude, float longitude);
    std::string getCode();
    std::string getName();
    std::string getCity();
    std::string getCountry();
    float getLatitude();
    float getLongitude();
};

#endif //AED2223_G29_AIRPORT_H
