//
// Created by diogotvf7 on 30-12-2022.
//

#include <iostream>
#include <iomanip>

#include "DataManager.h"
#include "Coordinate.h"

using namespace std;

class Test {
    template<class T>
    bool equals(T t1, T t2) {
        return t1 == t2;
    }

    template<class T>
    bool approximates(T t1, T t2, double gap) {
        return abs(t1 - t2) < gap;
    }

public:
    Test() {};

    void CSVReadTests() {
        cout << "CSVReadTests:\n"
                "_____________\n";
        DataManager dm;
        cout << "  Airlines reading test:\n";
        cout << "   :  " << (equals(dm.readAirlines(), 444) ? "Success" : "Failure") << '\n';

        cout << "  Airports reading test:\n";
        cout << "   :  " << (equals(dm.readAirports(), 3019) ? "Success" : "Failure") << '\n';

        cout << '\n';
    }

    void CoordinatesTests() {
        cout << "CoordinatesTests:\n"
                "_________________\n";

        Coordinate c1(75, 132);
        Coordinate c2(23.17593, 179.261115);
        cout << "  Distance calculation test 1:\n";
        cout << "   :  " << (approximates(c1.distanceTo(c2), 6361.01, 3) ? "Success" : "Failure") << '\n';

        Coordinate c3(-6.024290, 144.971000);
        Coordinate c4(4.398475,18.518786);
        cout << "  Distance calculation test 2:\n";
        cout << "   :  " << (approximates(c3.distanceTo(c4), 14084.9, 3) ? "Success" : "Failure") << '\n';

        cout << '\n';
    }

    void FlightGraphsTests() {
        cout << "FlightGraphsTests:\n"
                "__________________\n";

        DataManager dm;
        dm.readAirports();
        dm.readAirlines();

        FlightGraph g1 = dm.createFlightGraph();

        cout << "  Listing connected components test:\n";
        LLairports connectedComponents = g1.connectedComponents();
        int counter = 1;
        for (const Lairports &cc : connectedComponents) {
            cout << "\n_____________________________";
            cout << "\n   : Connected component " << counter++ << '\n';
            for (Airport *ap : cc)
                cout << "          -" << ap->getCode() << ' ' << setw(55) << left << ap->getName() << ap->getCountry() << '\n';
        }

        cout << '\n';
    }

    void runTests() {
        cout << '\n';
        CSVReadTests();
        CoordinatesTests();
        FlightGraphsTests();
    }
};