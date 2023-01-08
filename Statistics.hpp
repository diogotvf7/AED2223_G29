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

    void articulationAirports() {

        cout << setw(65) << right << "Articulation airports:\n";
        cout << setw(65) << right << "______________________\n";

        list<Airport*> artAirports = dm->getFlightsGraph()->getArticulationAirports();
        auto itr = artAirports.begin(); int i = 1;
        while (itr != artAirports.end()) {
            cout << setw(6) << right << i <<":" << setw(40) << right << (*itr)->getCode() << " " << (*itr)->getName() << '\n';
            itr++; i++;
        }

        cout << '\n';
    }

    void stronglyConnectedComponentsPlusDiameter() {

        cout << setw(65) << right << "Strongly Connected Components:\n";
        cout << setw(65) << right << "______________________________\n";

        list<list<Airport*>> sccs = dm->getFlightsGraph()->getStronglyConnectedComponents();
        list<Airport*> biggestComponent; int maxSize = 0;
        auto itr1 = sccs.begin(); int i = 1;
        while (itr1 != sccs.end()) {
            cout << "\n\nSCC " << i << ":    " << itr1->size() << " airports\n";
            if (itr1->size() > maxSize) {
                maxSize = (int) itr1->size();
                biggestComponent = *itr1;
            }
            auto itr2 = itr1->begin(); int j = 1;
            while (itr2 != itr1->end()) {
                if (j % 20 == 0) cout << '\n';
                cout << (*itr2)->getCode() << ' ';
                itr2++; j++;
            }
            itr1++; i++;
        }

        cout << '\n';
        cout << "Do you want to calcualte the diameter of the main component? This operation takes a lot of time. (yes/no): ";
        string _; cin >> _;
        if (_ != "yes") return;
        cout << setw(65) << right << "The diameter of the main component is: " << dm->getFlightsGraph()->getDiameter(biggestComponent);
        cout << setw(65) << right << "\n_____________________________________________\n";
    }

    void runStatistics() {
        cout << "\n_____________________________________________________\n";
        articulationAirports();
        stronglyConnectedComponentsPlusDiameter();
        cout << "\n_____________________________________________________\n";
        cout << "WRITE SOMETHING TO GO BACK"; string _; cin >> _;
    };
};