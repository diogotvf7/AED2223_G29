//
// Created by diogotvf7 on 29-12-2022.
//

#include "DataManager.h"

using namespace std;


UMairlines DataManager::getAirlines() const {
    return airlines;
}

UMairports DataManager::getAirports() const {
    return airports;
}

int DataManager::readAirlines() {

    ifstream csv("../dataset/airlines.csv");
    string line;
    getline(csv, line, '\n'); // Ignore Header

    while (getline(csv, line, '\n')) {

        string code, name, callsign, country;
        stringstream tmp(line);

        getline(tmp, code, ',');
        getline(tmp, name, ',');
        getline(tmp, callsign, ',');
        getline(tmp, country);

        airlines[code] = new Airline(code, name, callsign, country);
    }
    return (int) airlines.size();
}

int DataManager::readAirports() {

    ifstream csv("../dataset/airports.csv");
    string line;
    getline(csv, line, '\n'); // Ignore Header

    while (getline(csv, line, '\n')) {

        string code, name, city, country, latitude, longitude;
        stringstream tmp(line);

        getline(tmp, code, ',');
        getline(tmp, name, ',');
        getline(tmp, city, ',');
        getline(tmp, country, ',');
        getline(tmp, latitude, ',');
        getline(tmp, longitude, ',');

        airports[code] = new Airport(code, name, city, country, Coordinate(stod(latitude), stod(longitude)));
    }
    return (int) airports.size();
}

FlightGraph DataManager::createFlightGraph() {

    FlightGraph fg = FlightGraph(airports, airlines);

    ifstream csv("../dataset/flights.csv");
    string line;
    getline(csv, line, '\n'); // Ignore Header

    while (getline(csv, line, '\n')) {

        string source, target, airline;
        stringstream tmp(line);

        getline(tmp, source, ',');
        getline(tmp, target, ',');
        getline(tmp, airline);

        fg.addFlight(airports[source], airports[target], airlines[airline]);
    }
    return fg;
}
