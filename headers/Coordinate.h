//
// Created by diogotvf7 on 30-12-2022.
//

#ifndef AED2223_G29_COORDINATE_H
#define AED2223_G29_COORDINATE_H

#include <ostream>
#include <cmath>

class Coordinate {
    double latitude;
    double longitude;

public:
    /**
     * @brief Default constructor for the Coordinate class
     */
    Coordinate();
    /**
     * @brief Constructor for the Coordinate class
     * @param latitude the Coordinate's latitude
     * @param longitude the Coordinate's longitude
     */
    Coordinate(double latitude, double longitude);
    /**
     * @brief Get method for the latitude field
     * @return returns the value of the latitude field
     */
    [[nodiscard]] double getLatitude() const;
    /**
     * @brief Get method for the longitude field
     * @return returns the value of the longitude field
     */
    [[nodiscard]] double getLongitude() const;
    /**
     * @brief This function calculates the distance between two Coordinates using the Haversine's formula
     * @return returns the distance between the two Coordinates
     */
    [[nodiscard]] double distanceTo(Coordinate c2) const;

    /**
     * @brief Overload of the operator<< so that the Coordinate's can be easily printed using std::cout
     * @param os the output stream to which we want to output the Coordinate
     * @param coordinate the Coordinate we want to output
     * @return returns a reference to the original output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate);
};


#endif //AED2223_G29_COORDINATE_H
