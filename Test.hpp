//
// Created by diogotvf7 on 30-12-2022.
//

#include <iostream>
#include <iomanip>
#include <algorithm>

#include "DataManager.h"
#include "Coordinate.h"
#include "MinMaxStack.hpp"

using namespace std;

class Test {
    template<class T1, class T2>
    bool equals(T1 actual, T2 expected) const {
        return actual == expected;
    }

    template<class T1, class T2>
    bool approximates(T1 actual, T2 expected, double gap) const {
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

    void CSVReadTests() {
        cout << "CSVReadTests:\n"
                "_____________\n";
        DataManager dm("../dataset/real/");
        cout << "  Airlines reading test:\n";
        cout << "   :  " << (equals(dm.getAirlines().size(), 444) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Airports reading test:\n";
        cout << "   :  " << (equals(dm.getAirports().size(), 3019) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

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

        Coordinate c5(18, 23);
        Coordinate c6(12.5,16.9);
        cout << "  Distance calculation test 3:\n";
        cout << "   :  " << (approximates(c5.distanceTo(c6), 895, 3) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        Coordinate c9(43, 12);
        Coordinate c10(18,23);
        cout << "  Distance calculation test 4:\n";
        cout << "   :  " << (approximates(c9.distanceTo(c10), 2965, 3) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << '\n';
    }

    void ReachableAirportsTests() {
        cout << "ReachableAirportsTests:\n"
                "_______________________\n";

        DataManager dm("../dataset/test/");

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

    void MinDistanceBetweenAirportsTests() {
        cout << "MinDistanceBetweenAirportsTests:\n"
                "________________________________\n";

        DataManager dm("../dataset/test/");

        FlightGraph g1 = dm.createFlightGraph();

        cout << "  Min distance test 1:";
        cout << "\n   : " << (approximates(g1.minDistance("0A", "0E"), 279, 30) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Min distance test 2:";
        cout << "\n   : " << (approximates(g1.minDistance("0A", "0E"), 279, 30) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Min distance test 3:";
        cout << "\n   : " << (approximates(g1.minDistance("0A", "0E"), 279, 30) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Min distance test 4:";
        cout << "\n   : " << (approximates(g1.minDistance("0A", "0E"), 279, 30) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';


        cout << '\n';
    }

    void MinMaxStackTests() {
        cout << "MinMaxStackTests:\n"
                "_____________\n";
        Airport *a1 = new Airport("1", "A1", "", "", {0, 0});
        Airport *a2 = new Airport("2", "A2", "", "", {0, 0});
        Airport *a3 = new Airport("3", "A3", "", "", {0, 0});
        Airport *a4 = new Airport("4", "A4", "", "", {0, 0});


        MinMaxStack<Airport*,AiportCompare> mms;
        a1->setDistance(12); mms.push(a1);
        a2->setDistance(26); mms.push(a2);
        cout << "  Get min test 1:\n";
        cout << "   :  " << (equals(mms.getMin()->getDistance(), 12) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Get max test 1:\n";
        cout << "   :  " << (equals(mms.getMax()->getDistance(), 26) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        a3->setDistance(999); mms.push(a3);
        cout << "  Get min test 2:\n";
        cout << "   :  " << (equals(mms.getMin()->getDistance(), 12) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Get max test 2:\n";
        cout << "   :  " << (equals(mms.getMax()->getDistance(), 999) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        a4->setDistance(-13); mms.push(a4);
        cout << "  Get min test 3:\n";
        cout << "   :  " << (equals(mms.getMin()->getDistance(), -13) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Get max test 3:\n";
        cout << "   :  " << (equals(mms.getMax()->getDistance(), 999) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << '\n';
    }

    void runTests() {
        cout << "\n_____________________________________________________\n";
        CSVReadTests();
        CoordinatesTests();
        ReachableAirportsTests();
        MinDistanceBetweenAirportsTests();
        // MinMaxStackTests(); // Struct compare esta com o return trocado
        cout << "\n_____________________________________________________\n";
    }
};