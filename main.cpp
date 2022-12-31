#include <iostream>

#include "DataManager.h"
#include "Test.hpp"

using namespace std;

int main() {
    Test t; t.runTests();
    DataManager dm;
    dm.readAirports();
    dm.readAirlines();

    FlightGraph g1 = dm.createFlightGraph();
    return 0;
}
