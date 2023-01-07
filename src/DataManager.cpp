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
        if (countries.find(country) == countries.end())
            countries.emplace(country, new Country(country));
        countries[country]->addAirline(airlines[code]);
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
        if (countries.find(country) == countries.end())
            countries.emplace(country, new Country(country));
        countries[country]->addAirport(airports[code]);
        if (cities.find(city) == cities.end())
            cities.emplace(city, new City(city));
        cities[city]->addAirport(airports[code]);
        countries[country]->addAirport(airports[code]);
        countries[country]->addCity(cities[city]);
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

UMcountries DataManager::getCountries() const {
    return countries;
}

UMcities DataManager::getCities() const {
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

