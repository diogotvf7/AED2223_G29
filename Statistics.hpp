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
    DataManager dm;

public:

    Statistics(DataManager dm) : dm(dm) {
        dm.readAirlines();
        dm.readAirports();
    }

    void airportsByCountry() {

        cout << setw(58) << right << "Airports by country:\n";
        cout << setw(58) << right << "____________________\n";

        UMairports airports = dm.getAirports();
        map<string,int> freqTable;
        for (auto &[code, airport] : airports)
            freqTable[airport->getCountry()]++;
        for (auto &[country, freq] : freqTable)
            cout << "   :" << setw(40) << right << country << "  --  " << freq << " airports" << '\n';

        cout << '\n';
    }

    void airlinesByCountry() {

        cout << setw(58) << right << "Airlines by country:\n";
        cout << setw(58) << right << "____________________\n";

        UMairlines airlines = dm.getAirlines();
        map<string,int> freqTable;
        for (auto &[code, airline] : airlines)
            freqTable[airline->getCountry()]++;
        for (auto &[country, freq] : freqTable)
            cout << "   :" << setw(40) << right << country << "  --  " << freq << " airlines" << '\n';

        cout << '\n';
    }

    void runStatistics() {
        airportsByCountry();
        airlinesByCountry();
    };
};