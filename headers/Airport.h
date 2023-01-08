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
    bool token2;
    double distance;
    int num;
    int low;
    Airport *prev;

public:
    /**
     * @brief Constructor for the Airport class
     * @param code the Airport's code
     * @param name the Airport's name
     * @param city the Airport's city
     * @param country the Airport's country
     * @param coordinate the Airport's coordinate - {latitude, longitude}
     */
    Airport(std::string code, std::string name, std::string city, std::string country, Coordinate coordinate);
    /**
     * @brief Get method for the code field
     * @return returns the value of the code field
     */
    [[nodiscard]] std::string getCode() const;
    /**
     * @brief Get method for the name field
     * @return returns the value of the name field
     */
    [[nodiscard]] std::string getName() const;
    /**
     * @brief Get method for the city field
     * @return returns the value of the City field
     */
    [[nodiscard]] std::string getCity() const;
    /**
     * @brief Get method for the country field
     * @return returns the value of the Country field
     */
    [[nodiscard]] std::string getCountry() const;
    /**
     * @brief Get method for the coordinate field
     * @return returns the value of the Coordinate field
     */
    [[nodiscard]] Coordinate getCoordinate() const;
    /**
     * @brief Get method for the flights list field
     * @return returns the Flights list field
     */
    [[nodiscard]] std::list<Flight> getFlights() const;
    /**
     * @brief Get method for the graph traversal token field
     * @return returns the value of the graph traversal token field
     */
    [[nodiscard]] bool getToken() const;
    /**
     * @brief Get method for the graph traversal token2 field
     * @return returns the value of the graph traversal token2 field
     */
    [[nodiscard]] bool getToken2() const;
    /**
     * @brief Get method for the graph traversal distance field
     * @return returns the value of the graph traversal distance field
     */
    [[nodiscard]] double getDistance() const;
    /**
     * @brief Get method for the graph traversal num field
     * @return returns the value of the graph traversal num field
     */
    [[nodiscard]] int getNum() const;
    /**
     * @brief Get method for the graph traversal low field
     * @return returns the value of the graph traversal low field
     */
    [[nodiscard]] int getLow() const;
    /**
     * @brief Get method for the graph traversal prev field
     * @return returns the value of the graph traversal prev field
     */
    [[nodiscard]] Airport *getPrev() const;
    /**
     * @brief Set method for the graph traversal token field
     * @param token the new value that will be assigned to the field token
     */
    void setToken(bool token);
    /**
     * @brief Set method for the graph traversal token2 field
     * @param token2 the new value that will be assigned to the field token2
     */
    void setToken2(bool token2);
    /**
     * @brief Set method for the graph traversal distance field
     * @param distance the new value that will be assigned to the field distance
     */
    void setDistance(double distance);
    /**
     * @brief Set method for the graph traversal prev field
     * @param prev the new value that will be assigned to the field prev
     */
    void setPrev(Airport *prev);
    /**
     * @brief Set method for the graph traversal num field
     * @param num the new value that will be assigned to the field num
     */
    void setNum(int num);
    /**
     * @brief Set method for the graph traversal low field
     * @param low the new value that will be assigned to the field low
     */
    void setLow(int low);
    /**
     * @brief This function is used to add a Flight to the Airport's Flight list
     * @param f the Flight to be added
     */
    void addFlight(Flight f);
};

/**
 * This comparison struct is used so that we can
 * insert an Airport pointer in a priority queue.
 * This is useful to make the dijkstra min distance
 * algorithm.
 */
struct AirportCompare {
    bool operator()(const Airport *a1, const Airport *a2) {
        return a1->getDistance() > a2->getDistance();
    }
};
#endif //AED2223_G29_AIRPORT_H
