//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_FLIGHT_H
#define AED2223_G29_FLIGHT_H

#include "Airport.h"
#include "Airline.h"

class Airport;

class Flight {
    Airport *target;
    Airline *airline;
    double distance;

public:
    /**
     * @brief Constructor for the Flight Class
     * @param target the target Airport pointer
     * @param airline the pointer to the Flight's Airline
     * @param distance the weight of the Flight Edge
     */
    Flight(Airport *target, Airline *airline, double distance);
    /**
     * @brief Get method to the target Airport's pointer
     * @return returns a pointer to the target Airport
     */
    [[nodiscard]] Airport *getTarget() const;
    /**
     * @brief Get method to the Airline's pointer
     * @return returns a pointer to the Flight's Airline
     */
    [[nodiscard]] Airline *getAirline() const;
    /**
     * @brief Get method to the distance of the Flight
     * @return returns the distance between the source Airport and the target Airport's coordinates using the Haversine's formula
     */
    [[nodiscard]] double getDistance() const;
};

#endif //AED2223_G29_FLIGHT_H
