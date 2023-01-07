//
// Created by diogotvf7 on 02-01-2023.
//

#ifndef AED2223_G29_MENU_H
#define AED2223_G29_MENU_H

#include <iostream>
#include <iomanip>
#include <algorithm>

#include <vector>
#include <string>

#include "DataManager.h"

class Menu {
    DataManager *dm;
    std::string input;

public:
    Menu(DataManager *dm);

    void run();
    void mainMenu();
    void airportsMenu();
    bool airportInfo(Airport *source);
    bool reachableAirports(Airport *source);
    bool flightInfo(Airport *source, Airport *target);
    void countriesMenu();
    bool countryInfo(Country *country);
    void citiesMenu();
    bool cityInfo(City *city);
    void fastSearchMenu();

    void cleanTerminal();

};


#endif //AED2223_G29_MENU_H
