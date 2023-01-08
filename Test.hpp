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
        sort(actualCopy.begin(), actualCopy.end());
        sort(expectedCopy.begin(), expectedCopy.end());

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

        vector<string> actual;
        vector<string> expected;

        cout << "  Listing connected components test 1:";
        actual = dm.getFlightsGraph()->reachableAirports("0D");
        expected = {"0D", "0G", "0E", "0C", "0F"};
        cout << "\n   : " << (listUnsortedEquals(actual, expected) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Listing connected components test 2:";
        actual = dm.getFlightsGraph()->reachableAirports("1A");
        expected = {"1A", "1B", "1D"};
        cout << "\n   : " << (listUnsortedEquals(actual, expected) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Listing connected components test 3:";
        actual = dm.getFlightsGraph()->reachableAirports("2A");
        expected = {"2A", "2B"};
        cout << "\n   : " << (listUnsortedEquals(actual, expected) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Listing connected components test 4:";
        actual = dm.getFlightsGraph()->reachableAirports("0B");
        expected = {"0B"};
        cout << "\n   : " << (listUnsortedEquals(actual, expected) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << '\n';
    }

    void MinDistanceBetweenAirportsTests() {
        cout << "MinDistanceBetweenAirportsTests:\n"
                "________________________________\n";

        cout << "TESTS WITH FAKE DATA\n"
                "____________________\n\n";

        DataManager dmTest("../dataset/test/");

        cout << "  Min distance test 1:";
        cout << "\n   : " << (approximates(dmTest.getFlightsGraph()->minDistanceCodeCode("0A", "0E", false), 279, 30) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Min distance test 2:";
        cout << "\n   : " << (approximates(dmTest.getFlightsGraph()->minDistanceCodeCode("0A", "0E", false), 279, 30) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Min distance test 3:";
        cout << "\n   : " << (approximates(dmTest.getFlightsGraph()->minDistanceCodeCode("0A", "0E", false), 279, 30) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Min distance test 4:";
        cout << "\n   : " << (approximates(dmTest.getFlightsGraph()->minDistanceCodeCode("0A", "0E", false), 279, 30) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Min distance test 5:";
        cout << "\n   : " << (equals(dmTest.getFlightsGraph()->minDistanceCodeCode("1A", "1D", true), 1) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Min distance test 6:";
        cout << "\n   : " << (equals(dmTest.getFlightsGraph()->minDistanceCodeCode("1A", "1A", true), 0) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Min distance test 7:";
        cout << "\n   : " << (equals(dmTest.getFlightsGraph()->minDistanceCodeCode("1A", "1A", false), 0) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << '\n';

        cout << "TESTS WITH REAL DATA\n"
                "____________________\n\n";

        DataManager dmReal("../dataset/real/");

        cout << "  Min distance test 1:";
        cout << "\n   : " << (approximates(dmReal.getFlightsGraph()->minDistanceCodeCode("CIY", "CRL", false), 1740, 40) ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Min distance test 2:";
        auto test2 = dmReal.getFlightsGraph()->minDistanceCoordinateCoordinate({46.62588, -80.51849},{19.787141695223095,105.31429015741878},false, 30);
        cout << "\n   : " << (equals(test2.first->getCode(),"YSB") && equals(test2.second->getCode(),"THD") ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << "  Min distance test 3:";
        auto test3 = dmReal.getFlightsGraph()->minDistanceCoordinateCoordinate({51.75147740236968, 0.439787551256108},{-28.8028, 24.7652}, false, 30);
        cout << "\n   : " << (equals(test3.first->getCode(),"STN") && equals(test3.second->getCode(),"KIM") ? "Success\t\t\t\t\t\t\t\t\t\t√" : "Failure\t\t\t\t\t\t\t\t\t\tX") << '\n';

        cout << '\n';
    }

    void runTests() {
        cout << "\n_____________________________________________________\n";
        CSVReadTests();
        CoordinatesTests();
        ReachableAirportsTests();
        MinDistanceBetweenAirportsTests();
        cout << "\n_____________________________________________________\n";
        cout << "WRITE SOMETHING TO GO BACK"; string _; cin >> _;
    }
};