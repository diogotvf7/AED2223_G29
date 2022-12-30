//
// Created by diogotvf7 on 29-12-2022.
//

#include "DataManager.h"

using namespace std;


airlinesHT DataManager::getAirlines() const {
    return airlines;
}

airportsHT DataManager::getAirports() const {
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

        airlines.insert(Airline(code, name, callsign, country));
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

        airports.insert(Airport(code, name, city, country, stod(latitude), stod(longitude)));
    }
    return (int) airports.size();
}




/*
    ifstream in("../data/input/classes.csv");
    string line; getline(in, line, '\r'); // Ignore Header

    while (getline(in, line, '\r')) {

    string classCode, ucCode, weekday, start, duration, type;
    stringstream input(line);

    getline(input, classCode, ',');
    getline(input, ucCode, ',');
    getline(input, weekday, ',');
    getline(input, start, ',');
    getline(input, duration, ',');
    getline(input, type);

    auto itr = find_if(classes.begin(), classes.end(),[ucCode, classCode](Class *c){return c->getName() == classCode &&
                                                                                           c->getUc()->getName() == ucCode;});
    (*itr)->addSlot(new Slot(weekday, start, duration, type));
}*/
