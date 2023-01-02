//
// Created by diogotvf7 on 30-12-2022.
//

#include <iostream>
#include <iomanip>
#include <algorithm>

#include "DataManager.h"
#include "Coordinate.h"

using namespace std;

class Test {
    template<class T>
    bool equals(T actual, T expected) const {
        return actual == expected;
    }

    template<class T>
    bool approximates(T actual, T expected, double gap) const {
        return abs(actual - expected) < gap;
    }

    template<typename Container1, typename Container2>
    bool listUnsortedEquals(const Container1 &actual, const Container2 &expected) const {
        if (actual.size() != expected.size()) return false;

        Container1 actualCopy = actual;
        Container2 expectedCopy = expected;
        actualCopy.sort();
        expectedCopy.sort();

        auto itr1 = actualCopy.begin();
        auto itr2 = expectedCopy.begin();

        while (itr1 != actualCopy.end()) {
            if (*itr1 != *itr2) return false;
            itr1++; itr2++;
        }
        return true;
    }

public:
    Test() {};

    void CSVReadTests() {
        cout << "CSVReadTests:\n"
                "_____________\n";
        DataManager dm("../dataset/real/");
        cout << "  Airlines reading test:\n";
        cout << "   :  " << (equals(dm.readAirlines(), 444) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Airports reading test:\n";
        cout << "   :  " << (equals(dm.readAirports(), 3019) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << '\n';
    }

    void CoordinatesTests() {
        cout << "CoordinatesTests:\n"
                "_________________\n";

        Coordinate c1(75, 132);
        Coordinate c2(23.17593, 179.261115);
        cout << "  Distance calculation test 1:\n";
        cout << "   :  " << (approximates(c1.distanceTo(c2), 6361.01, 3) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        Coordinate c3(-6.024290, 144.971000);
        Coordinate c4(4.398475,18.518786);
        cout << "  Distance calculation test 2:\n";
        cout << "   :  " << (approximates(c3.distanceTo(c4), 14084.9, 3) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << '\n';
    }

    void FlightGraphsTests() {
        cout << "FlightGraphsTests:\n"
                "__________________\n";

        DataManager dm("../dataset/test/");
        dm.readAirports();
        dm.readAirlines();

        FlightGraph g1 = dm.createFlightGraph();
        list<string> actual;
        list<string> expected;

        cout << "  Listing connected components test 1:";
        actual = g1.reachableAirports("0D");
        expected = {"0D", "0G", "0E", "0C", "0F"};
        cout << "\n   : " << (listUnsortedEquals(actual, expected) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Listing connected components test 2:";
        actual = g1.reachableAirports("1A");
        expected = {"1A", "1B", "1D"};
        cout << "\n   : " << (listUnsortedEquals(actual, expected) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Listing connected components test 3:";
        actual = g1.reachableAirports("2A");
        expected = {"2A", "2B"};
        cout << "\n   : " << (listUnsortedEquals(actual, expected) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Listing connected components test 4:";
        actual = g1.reachableAirports("0B");
        expected = {"0B"};
        cout << "\n   : " << (listUnsortedEquals(actual, expected) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << '\n';
    }

    void runTests() {
        cout << '\n';
        CSVReadTests();
        CoordinatesTests();
        FlightGraphsTests();
    }
};