#include <iostream>

#include "DataManager.h"
#include "Test.hpp"
#include "Statistics.hpp"

using namespace std;

int main() {
    Test t; t.runTests();
    // Statistics s(dm); s.runStatistics();
    DataManager dm("../dataset/real/");
    dm.readAirports();
    dm.readAirlines();

    FlightGraph g1 = dm.createFlightGraph();
    return 0;
}
