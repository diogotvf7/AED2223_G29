//
// Created by diogotvf7 on 02-01-2023.
//

#include "Menu.h"

using namespace std;

string normalise(const string &s) {
    string lowerS;
    for (char c : s) lowerS += tolower(c);
    return lowerS;
}

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
                airportsMenu();
                input = "0";
                break;
            case 3:
                countriesMenu();
                input = "0";
                break;
            case 4:
                citiesMenu();
                input = "0";
                break;
            case 5:
                fastSearchMenu();
                input = "0";
                break;
            case 6: // EXIT
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
         << "|                              5. FAST SEARCH                                            |\n"
         << "|                              6. EXIT                                                   |\n"
         << "|________________________________________________________________________________________|\n\n";

    while (true) {
        cout << "   - OPTION: "; cin >> input;
        if ("1" <= input && input <= "6") break;
        else cout << "   - INVALID OPTION" << endl;
    }
}

void Menu::airportsMenu() {
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
             << "|                                   WRITE W TO MOVE UP                                   |\n"
             << "|                                  WRITE S TO MOVE DOWN                                  |\n"
             << "|                           WRITE MENU TO GO TO THE MAIN MENU                            |\n"
             << "|________________________________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> input;
            if (isNumerical(input) && page * 20 + 1 <= stoi(input) && stoi(input) <= min(page * 20 + 20, (int) airport.size())) {
                alive = reachableAirports(airportsCache[stoi(input) - 1]);
                break;
            } else if (normalise(input) == "w" && page * 20 - 20 >= 0) {
                page--;
                break;
            } else if (normalise(input) == "s" && page * 20 + 20 < (int) airport.size()) {
                page++;
                break;
            } else if (normalise(input) == "menu")
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

        for (int i = page * 20 + 1; i <= min(page * 20 + 20, (int) targets.size()); i++) {
            cout << right << setw(20) << to_string(i) + ".   " << left << setw(30)
                 << airports[targets[i]]->getCode() + " " + airports[targets[i]]->getName();
            cout << endl;
        }
        cout << "__________________________________________________________________________________________\n"
             << "|                           WRITE A NUMBER TO SEE AIRPORT MENU                           |\n"
             << "|                  WRITE A COUNTRY OR CITY's NAME TO SEE IT'S AIRPORTS                   |\n"
             << "|                                   WRITE W TO MOVE UP                                   |\n"
             << "|                                  WRITE S TO MOVE DOWN                                  |\n"
             << "|                         WRITE BACK TO GO TO THE PREVIOUS MENU                          |\n"
             << "|                           WRITE MENU TO GO TO THE MAIN MENU                            |\n"
             << "|________________________________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> input;
            if (isNumerical(input) && page * 20 + 1 <= stoi(input) && stoi(input) <= min(page * 20 + 20, (int) targets.size())) {
                alive = flightInfo(source, airports[targets[stoi(input)]]);
                break;
            } else if (normalise(input) == "w" && page * 20 - 20 >= 0) {
                page--;
                break;
            } else if (normalise(input) == "s" && page * 20 + 20 < (int) targets.size()) {
                page++;
                break;
            } else if (normalise(input) == "back")
                return true;
            else if (normalise(input) == "menu")
                return false;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
    return false;
}

bool Menu::flightInfo(Airport *source, Airport *target) {
    double minDistance = dm->getFlightsGraph()->minDistance(source->getCode(), target->getCode(), false);
    list<Airport*> minDistancePath = dm->getFlightsGraph()->path(source, target);
    // double minNumberFlights = dm->getFlightsGraph()->countFlights(source->getCode());
    double minNumberFlights = dm->getFlightsGraph()->minDistance(source->getCode(), target->getCode(), true);
    list<Airport*> minNumberFlightsPath = dm->getFlightsGraph()->path(source, target);

    bool alive = true;

    while (alive) {
        cleanTerminal();
        cout << "__________________________________________________________________________________________\n"
             << "|                                  FLIGHT INFORMATION                                    |\n"
             << "|                                                                                        |\n"
             << "|________________________________________________________________________________________|\n";
        cout << right << setw(5) << source->getCode() << " : " << setw(60) << left << source->getName() << ' ' << source->getCoordinate() << ' ' << source->getCountry() << endl;
        cout << right << setw(10)  << " to " << endl;
        cout << right << setw(5) << target->getCode() << " : " << setw(60) << left << target->getName() << ' ' << target->getCoordinate() << ' ' << target->getCountry() << endl;
        cout << "__________________________________________________________________________________________\n";
        cout << right << setw(20) << "Minimum distance: " << minDistance << " km;" << endl;
        auto itr1 = minDistancePath.begin(); int counter1 = 1;
        while (itr1 != minDistancePath.end()) {
            cout << right << setw(7) << counter1++ << ": " << (*itr1)->getCode() << ' ' << (*itr1++)->getName() << endl;
        }
        cout << "__________________________________________________________________________________________\n";
        cout << right << setw(20) << "Minimum number of flights: " << minNumberFlights << " flights;" << endl;
        auto itr2 = minNumberFlightsPath.begin(); int counter2 = 1;
        while (itr2 != minNumberFlightsPath.end()) {
            cout << right << setw(7) << counter2++ << ": " << (*itr2)->getCode() << ' ' << (*itr2++)->getName() << endl;
        }

        cout << "__________________________________________________________________________________________\n"
             << "|                         WRITE BACK TO GO TO THE PREVIOUS MENU                          |\n"
             << "|                           WRITE MENU TO GO TO THE MAIN MENU                            |\n"
             << "|________________________________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> input;
            if (isNumerical(input)) {
                break;
            } else if (normalise(input) == "back") {
                return true;
            } else if (normalise(input) == "menu") {
                return false;
            }

            else cout << "   - INVALID OPTION" << endl;
        }
    }
    return false;
}

void Menu::countriesMenu() {
    int page = 0;
    bool alive = true;
    UMcountries countries = dm->getCountries();
    auto itr = countries.begin();
    vector<Country*> countriesCache;
    while (alive) {
        cleanTerminal();
        cout << "__________________________________________________________________________________________\n"
             << "|                                       Countries                                        |\n"
             << "|                                   SELECT A COUNTRY                                     |\n"
             << "|________________________________________________________________________________________|\n";
        for (int i = page * 20; i < min(page * 20 + 20, (int) countries.size()); i++) {
            if (countriesCache.size() <= i) {
                countriesCache.push_back(itr->second);
                itr++;
            }
            cout << right << setw(20) << to_string(i) + ".   " << left << setw(30)
                 << countriesCache[i]->getName() << " : " << countriesCache[i]->getAirports().size() << " airports;" << endl;
        }
        cout << "__________________________________________________________________________________________\n"
             << "|                         WRITE A NUMBER TO SEE POSSIBLE TARGETS                         |\n"
             << "|                 WRITE A COUNTRY OR CITY's NAME TO FILTER IT'S AIRPORTS                 |\n"
             << "|                                   WRITE W TO MOVE UP                                   |\n"
             << "|                                  WRITE S TO MOVE DOWN                                  |\n"
             << "|                           WRITE MENU TO GO TO THE MAIN MENU                            |\n"
             << "|________________________________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> input;
            if (isNumerical(input) && page * 20 <= stoi(input) && stoi(input) <= min(page * 20 + 20, (int) countries.size())) {
                alive = countryInfo(countriesCache[stoi(input)]);
                break;
            } else if (normalise(input) == "w" && page * 20 - 20 >= 0) {
                page--;
                break;
            } else if (normalise(input) == "s" && page * 20 + 20 < (int) countries.size()) {
                page++;
                break;
            } else if (normalise(input) == "menu")
                return;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
}

bool Menu::countryInfo(Country *country) {
    bool alive = true;
    int page = 0;
    vector<City*> cities = country->getCities();
    vector<Airline*> airlines = country->getAirlines();
    vector<Airport*> airports = country->getAirports();
    int mode = 0;
    while (alive) {
        cleanTerminal();
        cout << "__________________________________________________________________________________________\n"
             << "|                                       Country                                          |\n"
             << "|                                   SELECT A COUNTRY                                     |\n"
             << "|________________________________________________________________________________________|\n";

        int maxIndex = (int) cities.size() * (mode == 0) + (int) airlines.size() * (mode == 1) + (int) airports.size() * (mode == 2);
        for (int i = page * 20; i < min(page * 20 + 20, maxIndex); i++) {
            if (mode == 0)
                cout << right << setw(20) << to_string(i + 1) + ".   " << right << setw(30)
                     << cities[i]->getName() << " : " << cities[i]->getAirports().size() << " airports;" << endl;
            else if (mode == 1)
                cout << right << setw(30) << to_string(i + 1) + ".   " << left << setw(30)
                     << airlines[i]->getName() << endl;
            else if (mode == 2)
                cout << right << setw(5) << to_string(i + 1) + ".   " << left << setw(30)
                     << airports[i]->getCode() << ' ' << setw(60) << left << airports[i]->getName() << airports[i]->getCoordinate() << endl;

        }
        cout << "__________________________________________________________________________________________\n";
        if (mode == 0)
            cout << "|                            WRITE A NUMBER TO GO TO CITY MENU                           |\n";
        if (mode == 2)
            cout << "|                           WRITE A NUMBER TO GO TO AIRPORT MENU                         |\n";
        cout << "|                             WRITE W OR S TO MOVE UP OR DOWN                            |\n"
             << "|                     WRITE A OR D TO TO GO TO PREVIOUS OR NEXT MODE                     |\n"
             << "|                         WRITE BACK TO GO TO THE PREVIOUS MENU                          |\n"
             << "|                           WRITE MENU TO GO TO THE MAIN MENU                            |\n"
             << "|________________________________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> input;
            if ((mode == 0 || mode == 2) && isNumerical(input) && page * 20 + 1 <= stoi(input) && stoi(input) <= min(page * 20 + 20, maxIndex - 1)) {
                if (mode == 0)
                    alive = cityInfo(dm->getCities()[cities[stoi(input)]->getName()]);
                else
                    alive = reachableAirports(dm->getAirports()[airports[stoi(input)]->getCode()]);
                break;
            } else if (normalise(input) == "w" && page * 20 - 20 >= 0) {
                page--;
                break;
            } else if (normalise(input) == "s" && page * 20 + 20 < (int) maxIndex - 1) {
                page++;
                break;
            } else if (normalise(input) == "a" && mode > 0) {
                page = 0;
                if (mode == 2 && airlines.empty()) mode--;
                mode--;
                break;
            } else if (normalise(input) == "d" && mode < 2) {
                page = 0;
                if (mode == 0 && airlines.empty()) mode++;
                mode++;
                break;
            } else if (normalise(input) == "back")
                return true;
            else if (normalise(input) == "menu")
                return false;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
    return false;
}

void Menu::citiesMenu() {

}

bool Menu::cityInfo(City *city) {
    return false;
}

void Menu::fastSearchMenu() {
    cleanTerminal();
    Airport *source = nullptr;
    Airport *target = nullptr;
    bool alive = true;

    while (alive) {
        cleanTerminal();
        cout << "__________________________________________________________________________________________\n"
             << "|                                    Fast search menu                                    |\n"
             << "|            Write the code of two airports to be your source and destination            |\n"
             << "|________________________________________________________________________________________|\n\n\n\n";
        while (true) {
            cout << right << setw(20) << "Source: "; cin >> input; cout << endl;
            if (dm->getAirports().find(input) != dm->getAirports().end()) {
                source = dm->getAirports()[input];
                break;
            }
            else
                cout << right << setw(20) << "Invalid code!";
        }
        vector<string> validOptions = dm->getFlightsGraph()->reachableAirports(source->getCode());
        while (true) {
            cout << right << setw(20) << "Target: "; cin >> input; cout << endl;
            if (dm->getAirports().find(input) != dm->getAirports().end() && find(validOptions.begin(), validOptions.end(), input) != validOptions.end()) {
                target= dm->getAirports()[input];
                break;
            }
            else
                cout << right << setw(20) << "Invalid code!";
        }
        alive = flightInfo(source, target);
    }

}

void Menu::cleanTerminal() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}



