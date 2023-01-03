#include <iostream>

#include "DataManager.h"
#include "Test.hpp"
#include "Statistics.hpp"
#include "Menu.h"

using namespace std;

int main() {
    Test t; t.runTests();
    // Statistics s(dm); s.runStatistics();
    DataManager dm("../dataset/real/");
    Menu menu(&dm);
    menu.run();

/*    FlightGraph g1 = dm.createFlightGraph();
    cout << g1.minDistance("MAG", "LAE");*/
    return 0;
}
