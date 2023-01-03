//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_AIRPORT_H
#define AED2223_G29_AIRPORT_H

#include <list>
#include <string>

#include "Flight.h"
#include "Coordinate.h"
#include "FlightGraph.h"

class Flight;

class Airport {
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    Coordinate coordinate;
    std::list<Flight> flights;
    // Graph traversal variables:
    bool token;
    double distance;

public:
    Airport(std::string code, std::string name, std::string city, std::string country, Coordinate coordinate);
    [[nodiscard]] std::string getCode() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getCity() const;
    [[nodiscard]] std::string getCountry() const;
    [[nodiscard]] Coordinate getCoordinate() const;
    [[nodiscard]] std::list<Flight> getFlights() const;
    [[nodiscard]] bool getToken() const;
    [[nodiscard]] double getDistance() const;
    void setToken(bool token);
    void setDistance(double distance);

    void addFlight(Flight f);
};

struct AiportCompare {
    bool operator()(const Airport *a1, const Airport *a2) {
        return a1->getDistance() < a2->getDistance();
    }
};
#endif //AED2223_G29_AIRPORT_H
