//
// Created by diogotvf7 on 29-12-2022.
//

#include "DataManager.h"

using namespace std;


DataManager::DataManager(std::string path) {
    this->path = path;
    readAirlines();
    readAirports();
    readFlights();
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
        Country *c = new Country(country);
        auto itr = countries.find(c);
        if (itr == countries.end()) {
            c->addAirline(airlines[code]);
            countries.insert(c);
        } else {
            delete c;
            (*itr)->addAirline(airlines[code]);
        }
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

        airports[code] = new Airport(code, name, city, country, Coordinate(stod(latitude), stod(longitude)));
        Country *c1 = new Country(country);
        auto itr1 = countries.find(c1);
        if (itr1 == countries.end()) {
            c1->addAirline(airlines[code]);
            countries.insert(c1);
        } else {
            delete c1;
            (*itr1)->addAirline(airlines[code]);
        }
        City *c2 = new City(city);
        auto itr2 = cities.find(c2);
        if (itr2 == cities.end()) {
            c2->addAirport(airports[code]);
            cities.insert(c2);
        } else {
            delete c2;
            (*itr2)->addAirport(airports[code]);
        }

    }
}

void DataManager::readFlights() {

    fg = new FlightGraph(airports, airlines);

    ifstream csv(path + "flights.csv");
    string line;
    getline(csv, line, '\n'); // Ignore Header

    while (getline(csv, line, '\n')) {

        string source, target, airline;
        stringstream tmp(line);

        getline(tmp, source, ',');
        getline(tmp, target, ',');
        getline(tmp, airline);

        fg->addFlight(airports[source], airports[target], airlines[airline]);
    }
}

UMairlines DataManager::getAirlines() const {
    return airlines;
}

UMairports DataManager::getAirports() const {
    return airports;
}

FlightGraph *DataManager::getFlightsGraph() const {
    return fg;
}

UScountries DataManager::getCountries() const {
    return countries;
}

UScities DataManager::getCities() const {
    return cities;
}

FlightGraph DataManager::createFlightGraph() {

    FlightGraph flightGraph = FlightGraph(airports, airlines);

    ifstream csv(path + "flights.csv");
    string line;
    getline(csv, line, '\n'); // Ignore Header

    while (getline(csv, line, '\n')) {

        string source, target, airline;
        stringstream tmp(line);

        getline(tmp, source, ',');
        getline(tmp, target, ',');
        getline(tmp, airline);

        flightGraph.addFlight(airports[source], airports[target], airlines[airline]);
    }
    return flightGraph;
}

