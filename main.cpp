#include <iostream>

#include "DataManager.h"

using namespace std;

int main() {

    DataManager dm;
    cout << dm.readAirlines() << '\n';
    cout << dm.readAirports() << '\n';

    return 0;
}
