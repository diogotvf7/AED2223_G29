//
// Created by diogotvf7 on 29-12-2022.
//

#include "DataManager.h"

using namespace std;


DataManager::DataManager(std::string path) {
    this->path = path;
    readAirlines();
    readAirports();
}


void DataManager::readAirlines() {

    ifstream csv(path + "/airlines.csv");
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
}

void DataManager::readAirports() {

    ifstream csv(path + "airports.csv");
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

        cities.insert(city);
        countries.insert(country);
        airports[code] = new Airport(code, name, city, country, Coordinate(stod(latitude), stod(longitude)));
    }
}

UMairlines DataManager::getAirlines() const {
    return airlines;
}

UMairports DataManager::getAirports() const {
    return airports;
}

uss DataManager::getCities() const {
    return cities;
}

uss DataManager::getCountries() const {
    return countries;
}

FlightGraph DataManager::createFlightGraph() {

    FlightGraph fg = FlightGraph(airports, airlines);

    ifstream csv(path + "flights.csv");
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
