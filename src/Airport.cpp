//
// Created by diogotvf7 on 29-12-2022.
//
#include "../headers/Airport.h"

using namespace std;

Airport::Airport(std::string code, std::string name, std::string city, std::string country, float latitude, float longitude) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
}

std::string Airport::getCode() {
    return code;
}

std::string Airport::getName() {
    return name;
}

std::string Airport::getCity() {
    return city;
}

std::string Airport::getCountry() {
    return country;
}

float Airport::getLatitude() {
    return latitude;
}

float Airport::getLongitude() {
    return longitude;
}

