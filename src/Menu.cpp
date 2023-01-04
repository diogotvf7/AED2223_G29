//
// Created by diogotvf7 on 02-01-2023.
//

#include "Menu.h"

using namespace std;

bool isNumerical(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

Menu::Menu(DataManager *dm) {
    this->dm = dm;
    input = "0";
}

void Menu::run() {

    bool alive = true;
    while (alive) {
        switch (stoi(input)) {

            case 0: // Main menu
                mainMenu();
                break;
            case 1:
                sourceMenu();
                input = "0";
                break;
            case 5: // EXIT
                cleanTerminal();
                alive = false;
                break;
        }
        cleanTerminal();
    }
}

void Menu::mainMenu() {
    cleanTerminal();
    cout << "__________________________________________________________________________________________\n"
         << "|                                       Main menu                                        |\n"
         << "|                              Choose an option to continue                              |\n"
         << "|________________________________________________________________________________________|\n"
         << "|                                                                                        |\n"
         << "|                              1. SEE AIRPORTS                                           |\n"
         << "|                              2. SEE AIRLINES                                           |\n"
         << "|                              3. SEE COUNTRIES                                          |\n"
         << "|                              4. SEE CITIES                                             |\n"
         << "|                              5. EXIT                                                   |\n"
         << "|________________________________________________________________________________________|\n\n";

    while (true) {
        cout << "   - OPTION: "; cin >> input;
        if ("1" <= input && input <= "5") break;
        else cout << "   - INVALID OPTION" << endl;
    }
}

void Menu::sourceMenu() {
    int page = 0;
    bool alive = true;
    UMairports airport = dm->getAirports();
    auto itr = airport.begin();
    vector<Airport*> airportsCache;
    while (alive) {
        cleanTerminal();
        cout << "__________________________________________________________________________________________\n"
             << "|                                       AIRPORTS                                         |\n"
             << "|                          SELECT AN AIRPORT TO BE YOUR SOURCE                           |\n"
             << "|________________________________________________________________________________________|\n";
        for (int i = page * 20; i < min(page * 20 + 20, (int) airport.size()); i++) {
            if (airportsCache.size() <= i) {
                airportsCache.push_back(itr->second);
                itr++;
            }
            cout << right << setw(20) << to_string(i + 1) + ".   " << left << setw(30)
                 << airportsCache[i]->getCode() + " " + airportsCache[i]->getName();
            cout << endl;
        }
        cout << "__________________________________________________________________________________________\n"
             << "|                         WRITE A NUMBER TO SEE POSSIBLE TARGETS                         |\n"
             << "|                 WRITE A COUNTRY OR CITY's NAME TO FILTER IT'S AIRPORTS                 |\n"
             << "|                                  WRITE 'w' TO MOVE UP                                  |\n"
             << "|                                 WRITE 's' TO MOVE DOWN                                 |\n"
             << "|                           WRITE 'menu' TO GO TO THE MAIN MENU                          |\n"
             << "|________________________________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> input;
            if (isNumerical(input) && page * 20 + 1 <= stoi(input) && stoi(input) <= min(page * 20 + 21, (int) airport.size())) {
                alive = reachableAirports(airportsCache[stoi(input) - 1]);
                break;
            } else if (input == "w" && page * 20 - 20 >= 0) {
                page--;
                break;
            } else if (input == "s" && page * 20 + 20 < (int) airport.size()) {
                page++;
                break;
            } else if (input == "menu")
                return;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
}

bool Menu::reachableAirports(Airport *source) {
    FlightGraph *fg = dm->getFlightsGraph();
    UMairports airports = dm->getAirports();
    std::vector<string> targets = fg->reachableAirports(source->getCode());
    int page = 0;
    bool alive = true;

    while (alive) {
        cleanTerminal();
        cout << "_________________________________________________________________________________________\n"
             << "|                                 POSSIBLE DESTINATIONS                                  |\n"
             << "|                       SELECT AN AIRPORT TO SEE FLIGHT INFORMATION                      |\n"
             << "|________________________________________________________________________________________|\n";

        for (int i = page * 20 + 1; i < min(page * 20 + 20, (int) targets.size()); i++) {
            cout << right << setw(20) << to_string(i) + ".   " << left << setw(30)
                 << airports[targets[i]]->getCode() + " " + airports[targets[i]]->getName();
            cout << endl;
        }
        cout << "__________________________________________________________________________________________\n"
             << "|                           WRITE A NUMBER TO SEE AIRPORT MENU                           |\n"
             << "|                  WRITE A COUNTRY OR CITY's NAME TO SEE IT'S AIRPORTS                   |\n"
             << "|                                  WRITE 'w' TO MOVE UP                                  |\n"
             << "|                                 WRITE 's' TO MOVE DOWN                                 |\n"
             << "|                           WRITE 'menu' TO GO TO THE MAIN MENU                          |\n"
             << "|________________________________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> input;
            if (isNumerical(input) && page * 20 + 1 <= stoi(input) && stoi(input) <= min(page * 20 + 21, (int) targets.size())) {
                alive = flightInfo(source, airports[targets[stoi(input)]]);
                break;
            } else if (input == "w" && page * 20 - 20 >= 0) {
                page--;
                break;
            } else if (input == "s" && page * 20 + 20 < (int) targets.size()) {
                page++;
                break;
            } else if (input == "menu")
                return false;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
    return false;
}

bool Menu::flightInfo(Airport *source, Airport *target) {
    double minDistance = dm->getFlightsGraph()->minDistance(source->getCode(), target->getCode());
    double minNumberFlights = dm->getFlightsGraph()->minDistance(source->getCode(), target->getCode(), true);

    bool alive = true;

    while (alive) {
        cleanTerminal();
        cout << "__________________________________________________________________________________________\n"
             << "|                                  FLIGHT INFORMATION                                    |\n"
             << "|                                                                                        |\n"
             << "|________________________________________________________________________________________|\n";
        cout << right << setw(5) << source->getCode() << " : " << setw(60) << left << source->getName() << ' ' << source->getCoordinate() << ' ' << source->getCountry() << endl;
        cout << right << setw(10)  << " to " << endl;
        cout << right << setw(5) << source->getCode() << " : " << setw(60) << left << target->getName() << ' ' << target->getCoordinate() << ' ' << target->getCountry() << endl;
        cout << "__________________________________________________________________________________________\n";
        cout << right << setw(20) << "Minimum distance: " << minDistance << " km;" << endl;
        cout << right << setw(20) << "Minimum number of flights: " << minNumberFlights << " flights;" << endl;

        cout << "__________________________________________________________________________________________\n"
             << "|                           WRITE A NUMBER TO SEE AIRPORT MENU                           |\n"
             << "|                  WRITE A COUNTRY OR CITY's NAME TO SEE IT'S AIRPORTS                   |\n"
             << "|________________________________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> input;
            if (isNumerical(input)) {
                break;
            } else if (input == "back") {
                return true;
            } else if (input == "menu") {
                return false;
            }

            else cout << "   - INVALID OPTION" << endl;
        }
    }
    return false;
}

void Menu::cleanTerminal() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

