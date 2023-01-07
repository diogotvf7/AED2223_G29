//
// Created by diogotvf7 on 30-12-2022.
//

#include <iostream>
#include <iomanip>
#include <map>

#include "DataManager.h"
#include "Coordinate.h"

using namespace std;

class Statistics {
    DataManager *dm;

public:
    Statistics(DataManager *dm) {
        this->dm = dm;
    }

    void airportsByCountry() {

        cout << setw(58) << right << "Airports by country:\n";
        cout << setw(58) << right << "____________________\n";

        UMcountries countries = dm->getCountries();
        for (auto &[code, country] : countries)
            cout << "   :" << setw(40) << right << country->getName() << "  --  " << country->getAirports().size() << " airports" << '\n';

        cout << '\n';
    }

    void airlinesByCountry() {

        cout << setw(58) << right << "Airlines by country:\n";
        cout << setw(58) << right << "____________________\n";

        UMcountries countries = dm->getCountries();
        for (auto &[code, country] : countries)
            cout << "   :" << setw(40) << right << country->getName() << "  --  " << country->getAirlines().size() << " airlines" << '\n';

        cout << '\n';
    }

    void citiesWithMoreThanOneAirport() {

        cout << setw(65) << right << "Cities with more than one airport:\n";
        cout << setw(65) << right << "__________________________________\n";

        UMcities cities = dm->getCities();
        auto itr = cities.begin();
        while (itr != cities.end()) {
            if (itr->second->getAirports().size() > 1)
                cout << "   :" << setw(40) << right << itr->first << "  --  " << itr->second->getAirports().size() << " airports" << '\n';
            itr++;
        }
    }

    void runStatistics() {
        cout << "\n_____________________________________________________\n";
        airportsByCountry();
        airlinesByCountry();
        citiesWithMoreThanOneAirport();
        cout << "\n_____________________________________________________\n";
        cout << "WRITE SOMETHING TO GO BACK"; string _; cin >> _;
    };
};