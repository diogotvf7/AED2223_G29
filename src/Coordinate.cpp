//
// Created by diogotvf7 on 30-12-2022.
//

#include "Coordinate.h"


Coordinate::Coordinate() {}

Coordinate::Coordinate(double latitude, double longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
}

double Coordinate::getLatitude() const {
    return latitude;
}

double Coordinate::getLongitude() const {
    return longitude;
}

double Coordinate::distanceTo(Coordinate c2) const {

    double lat1 = latitude * M_PI / 180;
    double lat2 = c2.latitude * M_PI / 180;

    double dLat = (c2.latitude - latitude) * M_PI / 180;
    double dLon = (c2.longitude - longitude) * M_PI / 180;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);

    return 12742 * asin(sqrt(a));
}

