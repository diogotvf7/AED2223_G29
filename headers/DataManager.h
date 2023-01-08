//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_DATAMANAGER_H
#define AED2223_G29_DATAMANAGER_H

#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

#include "Airline.h"
#include "Airport.h"
#include "FlightGraph.h"
#include "City.h"
#include "Country.h"

typedef std::unordered_map<std::string, Airline*> UMairlines;
typedef std::unordered_map<std::string, Airport*> UMairports;
typedef std::unordered_map<std::string, City*> UMcities;
typedef std::unordered_map<std::string, Country*> UMcountries;

class DataManager {
    std::string path;
    UMairlines airlines;
    UMairports airports;
    UMcities cities;
    UMcountries countries;
    FlightGraph *fg;

    /**
     * @brief This function reads the airlines.csv file
     */
    void readAirlines();
    /**
     * @brief This function reads the airports.csv file
     */
    void readAirports();
    /**
     * @brief This function reads the flights.csv file
     */
    void readFlights();
public:
    /**
     * @brief Constructor for the DataManager class
     * @param path the path from where the data will be read
     */
    explicit DataManager(std::string path);
    /**
     * @brief Get method for the Airline's unordered_map field
     * @return returns the Airline's unordered_map field
     */
    UMairlines getAirlines() const;
    /**
     * @brief Get method for the Airport's unordered_map field
     * @return returns the Airport's unordered_map field
     */
    UMairports getAirports() const;
    /**
     * @brief Get method for the Countrie's unordered_map field
     * @return returns the Countrie's unordered_map field
     */
    UMcountries getCountries() const;
    /**
     * @brief Get method for the Citie's unordered_map field
     * @return returns the Citie's unordered_map field
     */
    UMcities getCities() const;
    /**
     * @brief Get method for the DataManager's FlightGraph
     * @return returns the DataManager's FlightGraph
     */
    FlightGraph *getFlightsGraph() const;
};


#endif //AED2223_G29_DATAMANAGER_H
