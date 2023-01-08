//
// Created by diogotvf7 on 02-01-2023.
//

#ifndef AED2223_G29_MENU_H
#define AED2223_G29_MENU_H

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <regex>
#include <sstream>

#include <vector>
#include <string>

#include "DataManager.h"

class Menu {
    DataManager *dm;
    std::string input;

public:
    /**
     * @brief Constructor for the class Menu
     * @param dm a pointer the Menu's DataManager
     */
    Menu(DataManager *dm);
    /**
     * @brief This function runs the menu
     */
    void run();
    /**
     * @brief This function prints the main menu options
     */
    void mainMenu();
    /**
     * @brief This function prints all the Airports. If you select one you can choose between seeing it's information or seeing it's possible targets
     */
    void airportsMenu();
    /**
     * @brief This function prints the information about an Airport (reachable Airports, Countries, Cities in n flights; Airlines used in n flights)
     * @param source a pointer to the selected Airport
     * @return returns true if the user intends to go to the previous menu, otherwise returns false and the used will go to the main menu
     */
    bool airportInfo(Airport *source);
    /**
     * @brief This function prints all the reachable airports form {source}
     * @param source a pointer to the source Airport
     * @return returns true if the user intends to go to the previous menu, otherwise returns false and the used will go to the main menu
     */
    bool reachableAirports(Airport *source);
    /**
     * @brief This function prints the information of a flight from {source} to {target} (minimum distance and minimum number of flights)
     * @param source a pointer to the source Airport
     * @param target a pointer to the target Airport
     * @return returns true if the user intends to go to the previous menu, otherwise returns false and the used will go to the main menu
     */
    bool flightInfo(Airport *source, Airport *target);
    /**
     * @brief This function prints all the Countries. If you select one you will go to the Country Info menu
     */
    void countriesMenu();
    /**
     * @brief This function prints all the Airports or Airlines or Cities from that Country
     * @param country a pointer to the selected Country
     * @return returns true if the user intends to go to the previous menu, otherwise returns false and the used will go to the main menu
     */
    bool countryInfo(Country *country);
    /**
     * @brief This function prints all the Cities. If you select one you will go to the City Info menu
     */
    void citiesMenu();
    /**
     * @brief This functions prints all the Airports in a City
     * @param city a pointer to the selected City
     * @return returns true if the user intends to go to the previous menu, otherwise returns false and the used will go to the main menu
     */
    bool cityInfo(City *city);
    /**
     * @brief This menu provides many search combinations (ex.: source Coordinate - target City; source Airport - target Country; etc)
     */
    void fastSearchMenu();
    /**
     * @brief This function prints many new line characters to clear the terminal
     */
    void cleanTerminal();
};


#endif //AED2223_G29_MENU_H
