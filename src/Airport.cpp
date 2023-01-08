//
// Created by diogotvf7 on 29-12-2022.
//
#include "../headers/Airport.h"

using namespace std;

Airport::Airport(string code, string name, string city, string country, Coordinate coordinate) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->coordinate = coordinate;

    token = false;
    distance = 0;
}

string Airport::getCode() const {
    return code;
}

string Airport::getName() const {
    return name;
}

string Airport::getCity() const {
    return city;
}

string Airport::getCountry() const {
    return country;
}

Coordinate Airport::getCoordinate() const {
    return coordinate;
}

std::list<Flight> Airport::getFlights() const {
    return flights;
}

bool Airport::getToken() const {
    return token;
}

bool Airport::getToken2() const {
    return token2;
}

double Airport::getDistance() const {
    return distance;
}

int Airport::getNum() const {
    return num;
}

int Airport::getLow() const {
    return low;
}

int Airport::getDiameter() const {
    return diameter;
}

Airport *Airport::getPrev() const {
    return prev;
}

void Airport::setToken(bool token) {
    this->token = token;
}

void Airport::setToken2(bool token2) {
    this->token2 = token2;
}

void Airport::setDistance(double distance) {
    this->distance = distance;
}

void Airport::setNum(int num) {
    this->num = num;
}

void Airport::setLow(int low) {
    this->low = low;
}

void Airport::setDiameter(int diameter) {
    this->diameter = diameter;
}

void Airport::setPrev(Airport *prev) {
    this->prev = prev;
}

void Airport::addFlight(Flight f) {
    flights.push_back(f);
}





