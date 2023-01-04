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
    Coordinate();
    Coordinate(double latitude, double longitude);

    double getLatitude() const;
    double getLongitude() const;
    double distanceTo(Coordinate c2) const;

    friend std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate);
};


#endif //AED2223_G29_COORDINATE_H
