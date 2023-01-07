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
    cout << "__________________________________________________________________________________________________________________________________\n"
         << "|                                                           Main menu                                                            |\n"
         << "|                                                  Choose an option to continue                                                  |\n"
         << "|________________________________________________________________________________________________________________________________|\n"
         << "|                                                                                                                                |\n"
         << "|                                                  1. SEE AIRPORTS                                                               |\n"
         << "|                                                  2. SEE AIRLINES                                                               |\n"
         << "|                                                  3. SEE COUNTRIES                                                              |\n"
         << "|                                                  4. SEE CITIES                                                                 |\n"
         << "|                                                  5. FAST SEARCH                                                                |\n"
         << "|                                                  6. EXIT                                                                       |\n"
         << "|________________________________________________________________________________________________________________________________|\n\n";

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
        cout << "__________________________________________________________________________________________________________________________________\n"
             << "|                                                           AIRPORTS                                                             |\n"
             << "|                                              SELECT AN AIRPORT TO BE YOUR SOURCE                                               |\n"
             << "|________________________________________________________________________________________________________________________________|\n";
        for (int i = page * 20; i < min(page * 20 + 20, (int) airport.size()); i++) {
            if (airportsCache.size() <= i) {
                airportsCache.push_back(itr->second);
                itr++;
            }
            cout << right << setw(20) << to_string(i + 1) + ".   " << left << setw(30)
                 << airportsCache[i]->getCode() + " " + airportsCache[i]->getName() << endl;
        }
        cout << "__________________________________________________________________________________________________________________________________\n"
             << "|                                             WRITE A NUMBER TO SEE POSSIBLE TARGETS                                             |\n"
             << "|                                     WRITE A COUNTRY OR CITY's NAME TO FILTER IT'S AIRPORTS                                     |\n"
             << "|                                                       WRITE W TO MOVE UP                                                       |\n"
             << "|                                                      WRITE S TO MOVE DOWN                                                      |\n"
             << "|                                               WRITE MENU TO GO TO THE MAIN MENU                                                |\n"
             << "|________________________________________________________________________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> input;
            string tmp = input;
            if (isNumerical(input) && page * 20 + 1 <= stoi(input) && stoi(input) <= min(page * 20 + 20, (int) airport.size())) {
                while (true) {
                    cout << "   - 1. Display airport info" << endl
                         << "   - 2. Display possible targets" << endl;
                    cin >> input;
                    if (input == "1")
                        alive = airportInfo(airportsCache[stoi(tmp) - 1]);
                    if (input == "2")
                         alive = reachableAirports(airportsCache[stoi(tmp) - 1]);
                    break;
                }
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

bool Menu::airportInfo(Airport *source) {
    bool alive = true;
    int page = 0;
    int mode = 0, gap = 3;
    unordered_set<string> targets = dm->getFlightsGraph()->airportsInNFlights(source->getCode(), gap);
    auto itr = targets.begin();
    vector<string> cache;
    while (alive) {
        cleanTerminal();
        string header = source->getCode() + "   " + source->getName();
        cout << "__________________________________________________________________________________________________________________________________\n"
             << "|" << setw(65 + (int) header.size() / 2) << right << header << setw(65 - (int) header.size() / 2) << right << " |\n";
        if (mode == 0) cout << "|                                     DISPLAYING POSSIBLE TARGET AIRPORTS IN " << setw(2) << left << gap << " FLIGHTS                                          |\n";
        if (mode == 1) cout << "|                                    DISPLAYING POSSIBLE TARGET COUNTRIES IN " << setw(2) << left << gap << " FLIGHTS                                          |\n";
        if (mode == 2) cout << "|                                       DISPLAYING POSSIBLE TARGET CITIES IN " << setw(2) << left << gap << " FLIGHTS                                          |\n";
        if (mode == 3) cout << "|                                          DISPLAYING POSSIBLE AIRLINES IN " << setw(2) << left << gap << " FLIGHTS                                            |\n";
        cout << "|                                                THERE ARE "<< setw(4) << right << targets.size() << " POSSIBLE OPTIONS                                                 |\n" <<
                "|________________________________________________________________________________________________________________________________|\n";
        for (int i = page * 20; i < min(page * 20 + 20, (int) targets.size()); i++) {
            if (cache.size() <= i) {
                cache.push_back(*itr);
                itr++;
            }
            cout << right << setw(20) << to_string(i + 1) + ".   " << right << setw(30)
                 << cache[i] << endl;
        }
        cout << "__________________________________________________________________________________________________________________________________\n";
        if (mode == 0)
            cout << "|                                                WRITE A NUMBER TO GO TO FLIGHT MENU                                             |\n";
        if (mode == 1)
            cout << "|                                                WRITE A NUMBER TO GO TO COUNTRY MENU                                            |\n";
        if (mode == 2)
            cout << "|                                                 WRITE A NUMBER TO GO TO CITY MENU                                              |\n";
        cout << "|                                                 WRITE W OR S TO MOVE UP OR DOWN                                                |\n";
        if (mode == 0) cout << "|                                                   WRITE D TO GO TO NEXT MODE                                                   |\n";
        else if (mode == 1 || mode == 2) cout << "|                                           WRITE A OR D TO GO TO PREVIOUS OR NEXT MODE                                          |\n";
        else if (mode == 3) cout << "|                                                 WRITE A TO GO TO PREVIOUS MODE                                                 |\n";
        if (gap == 1) cout << "|                                                WRITE U TO INCREASE MAX FLIGHTS                                                |\n";
        if (1 < gap && gap < 9) cout << "|                                        WRITE U OR J TO INCREASE OR DECREASE MAX FLIGHTS                                        |\n";
        if (gap == 9) cout << "|                                                WRITE J TO DECREASE MAX FLIGHTS                                                |\n";
        cout << "|                                             WRITE BACK TO GO TO THE PREVIOUS MENU                                              |\n"
             << "|                                               WRITE MENU TO GO TO THE MAIN MENU                                                |\n"
             << "|________________________________________________________________________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> input;
            if (mode < 3 && isNumerical(input) && page * 20 + 1 <= stoi(input) && stoi(input) <= min(page * 20 + 20, (int) targets.size() - 1)) {
                if (mode == 0)
                    alive = flightInfo(source, dm->getAirports()[cache[stoi(input) - 1]]);
                else if (mode == 1)
                    alive = countryInfo(dm->getCountries()[cache[stoi(input) - 1]]);
                else if (mode == 2)
                    alive = cityInfo(dm->getCities()[cache[stoi(input) - 1]]);
                break;
            } else if (normalise(input) == "w" && page * 20 - 20 >= 0) {
                page--;
                break;
            } else if (normalise(input) == "s" && page * 20 + 20 < (int) targets.size() - 1) {
                page++;
                break;
            } else if (normalise(input) == "a" && mode > 0) {
                page = 0;
                if (mode == 1) targets = dm->getFlightsGraph()->airportsInNFlights(source->getCode(), gap);
                if (mode == 2) targets = dm->getFlightsGraph()->countriesInNFlights(source->getCode(), gap);
                if (mode == 3) targets = dm->getFlightsGraph()->citiesInNFlights(source->getCode(), gap);
                itr = targets.begin(); cache.clear(); mode--;
                break;
            } else if (normalise(input) == "d" && mode < 3) {
                page = 0;
                if (mode == 0) targets = dm->getFlightsGraph()->countriesInNFlights(source->getCode(), gap);
                if (mode == 1) targets = dm->getFlightsGraph()->citiesInNFlights(source->getCode(), gap);
                if (mode == 2) targets = dm->getFlightsGraph()->airlinesInNFlights(source->getCode(), gap);
                itr = targets.begin(); cache.clear(); mode++;
                break;
            } else if (normalise(input) == "u" && 1 <= gap && gap < 9) {
                page = 0; gap++;
                if (mode == 0) targets = dm->getFlightsGraph()->airportsInNFlights(source->getCode(), gap);
                if (mode == 1) targets = dm->getFlightsGraph()->countriesInNFlights(source->getCode(), gap);
                if (mode == 2) targets = dm->getFlightsGraph()->citiesInNFlights(source->getCode(), gap);
                if (mode == 3) targets = dm->getFlightsGraph()->airlinesInNFlights(source->getCode(), gap);
                itr = targets.begin(); cache.clear();
                break;
            } else if (normalise(input) == "j" && 1 < gap && gap <= 9) {
                page = 0; gap--;
                if (mode == 0) targets = dm->getFlightsGraph()->airportsInNFlights(source->getCode(), gap);
                if (mode == 1) targets = dm->getFlightsGraph()->countriesInNFlights(source->getCode(), gap);
                if (mode == 2) targets = dm->getFlightsGraph()->citiesInNFlights(source->getCode(), gap);
                if (mode == 3) targets = dm->getFlightsGraph()->airlinesInNFlights(source->getCode(), gap);
                itr = targets.begin(); cache.clear();
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

bool Menu::reachableAirports(Airport *source) {
    FlightGraph *fg = dm->getFlightsGraph();
    UMairports airports = dm->getAirports();
    std::vector<string> targets = fg->reachableAirports(source->getCode());
    int page = 0;
    bool alive = true;

    while (alive) {
        cleanTerminal();
        string header = source->getCode() + "   " + source->getName();
        cout << "__________________________________________________________________________________________________________________________________\n"
             << "|" << setw(65 + (int) header.size() / 2) << right << header << setw(65 - (int) header.size() / 2) << right << " |\n"
             << "|                                           SELECT AN AIRPORT TO SEE FLIGHT INFORMATION                                          |\n"
             << "|________________________________________________________________________________________________________________________________|\n";
        for (int i = page * 20 + 1; i <= min(page * 20 + 20, (int) targets.size()); i++) {
            cout << right << setw(20) << to_string(i) + ".   " << left << setw(30)
                 << airports[targets[i]]->getCode() + " " + airports[targets[i]]->getName();
            cout << endl;
        }
        cout << "__________________________________________________________________________________________________________________________________\n"
             << "|                                               WRITE A NUMBER TO SEE AIRPORT MENU                                               |\n"
             << "|                                      WRITE A COUNTRY OR CITY's NAME TO SEE IT'S AIRPORTS                                       |\n"
             << "|                                                       WRITE W TO MOVE UP                                                       |\n"
             << "|                                                      WRITE S TO MOVE DOWN                                                      |\n"
             << "|                                             WRITE BACK TO GO TO THE PREVIOUS MENU                                              |\n"
             << "|                                               WRITE MENU TO GO TO THE MAIN MENU                                                |\n"
             << "|________________________________________________________________________________________________________________________________|\n\n";

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
    double minNumberFlights = dm->getFlightsGraph()->minDistance(source->getCode(), target->getCode(), true);
    list<Airport*> minNumberFlightsPath = dm->getFlightsGraph()->path(source, target);

    bool alive = true;

    while (alive) {
        cleanTerminal();
        cout << "__________________________________________________________________________________________________________________________________\n"
             << "|                                                      FLIGHT INFORMATION                                                        |\n"
             << "|                                                                                                                                |\n"
             << "|________________________________________________________________________________________________________________________________|\n";
        cout << right << setw(5) << source->getCode() << " : " << setw(60) << left << source->getName() << ' ' << source->getCoordinate() << ' ' << source->getCountry() << endl;
        cout << right << setw(10)  << " to " << endl;
        cout << right << setw(5) << target->getCode() << " : " << setw(60) << left << target->getName() << ' ' << target->getCoordinate() << ' ' << target->getCountry() << endl;
        cout << "__________________________________________________________________________________________________________________________________\n";
        cout << right << setw(20) << "Minimum distance: " << minDistance << " km;" << endl;
        auto itr1 = minDistancePath.begin(); int counter1 = 1;
        while (itr1 != minDistancePath.end()) {
            cout << right << setw(7) << counter1++ << ": " << (*itr1)->getCode() << ' ' << (*itr1++)->getName() << endl;
        }
        cout << "__________________________________________________________________________________________________________________________________\n";
        cout << right << setw(20) << "Minimum number of flights: " << minNumberFlights << " flights;" << endl;
        auto itr2 = minNumberFlightsPath.begin(); int counter2 = 1;
        while (itr2 != minNumberFlightsPath.end()) {
            cout << right << setw(7) << counter2++ << ": " << (*itr2)->getCode() << ' ' << (*itr2++)->getName() << endl;
        }

        cout << "__________________________________________________________________________________________________________________________________\n"
             << "|                                             WRITE BACK TO GO TO THE PREVIOUS MENU                                              |\n"
             << "|                                               WRITE MENU TO GO TO THE MAIN MENU                                                |\n"
             << "|________________________________________________________________________________________________________________________________|\n\n";

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
        cout << "__________________________________________________________________________________________________________________________________\n"
             << "|                                                           Countries                                                            |\n"
             << "|                                                       SELECT A COUNTRY                                                         |\n"
             << "|________________________________________________________________________________________________________________________________|\n";
        for (int i = page * 20; i < min(page * 20 + 20, (int) countries.size()); i++) {
            if (countriesCache.size() <= i) {
                countriesCache.push_back(itr->second);
                itr++;
            }
            cout << right << setw(20) << to_string(i) + ".   " << left << setw(30)
                 << countriesCache[i]->getName() << " : " << countriesCache[i]->getAirports().size() << " airports;" << endl;
        }
        cout << "__________________________________________________________________________________________________________________________________\n"
             << "|                                                       WRITE W TO MOVE UP                                                       |\n"
             << "|                                                      WRITE S TO MOVE DOWN                                                      |\n"
             << "|                                               WRITE MENU TO GO TO THE MAIN MENU                                                |\n"
             << "|________________________________________________________________________________________________________________________________|\n\n";

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
        string header = country->getName();
        cout << "__________________________________________________________________________________________________________________________________\n"
             << "|" << setw(65 + (int) header.size() / 2) << right << header << setw(65 - (int) header.size() / 2) << right << " |\n";
        if (mode == 0) cout << "|                                                      DISPLAYING CITIES                                                         |\n";
        else if (mode == 1) cout << "|                                                     DISPLAYING AIRLINES                                                        |\n";
        else if (mode == 2) cout << "|                                                     DISPLAYING AIRPORTS                                                        |\n";
        cout << "|________________________________________________________________________________________________________________________________|\n";

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
        cout << "__________________________________________________________________________________________________________________________________\n";
        if (mode == 0)
            cout << "|                                                WRITE A NUMBER TO GO TO CITY MENU                                               |\n";
        if (mode == 2)
            cout << "|                                               WRITE A NUMBER TO GO TO AIRPORT MENU                                             |\n";
        cout << "|                                                 WRITE W OR S TO MOVE UP OR DOWN                                                |\n";
        if (mode == 0) cout << "|                                                   WRITE D TO GO TO NEXT MODE                                                   |\n";
        if (mode == 1) cout << "|                                           WRITE A OR D TO GO TO PREVIOUS OR NEXT MODE                                          |\n";
        if (mode == 2) cout << "|                                                 WRITE A TO GO TO PREVIOUS MODE                                                 |\n";
        cout << "|                                             WRITE BACK TO GO TO THE PREVIOUS MENU                                              |\n"
             << "|                                               WRITE MENU TO GO TO THE MAIN MENU                                                |\n"
             << "|________________________________________________________________________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> input;
            if ((mode == 0 || mode == 2) && isNumerical(input) && page * 21 <= stoi(input) && stoi(input) <= min(page * 20 + 20, maxIndex)) {
                if (mode == 0)
                    alive = cityInfo(dm->getCities()[cities[stoi(input) - 1]->getName()]);
                else
                    alive = reachableAirports(dm->getAirports()[airports[stoi(input) - 1]->getCode()]);
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
    int page = 0;
    bool alive = true;
    UMcities cities = dm->getCities();
    auto itr = cities.begin();
    vector<City*> citiesCache;
    while (alive) {
        cleanTerminal();
        cout << "__________________________________________________________________________________________________________________________________\n"
             << "|                                                             Cities                                                             |\n"
             << "|                                                         SELECT A CITY                                                          |\n"
             << "|________________________________________________________________________________________________________________________________|\n";
        for (int i = page * 20; i < min(page * 20 + 20, (int) cities.size()); i++) {
            if (citiesCache.size() <= i) {
                citiesCache.push_back(itr->second);
                itr++;
            }
            cout << right << setw(20) << to_string(i) + ".   " << left << setw(30)
                 << citiesCache[i]->getName() << " : " << citiesCache[i]->getAirports().size() << " airports;" << endl;
        }
        cout << "__________________________________________________________________________________________________________________________________\n"
             << "|                                                       WRITE W TO MOVE UP                                                       |\n"
             << "|                                                      WRITE S TO MOVE DOWN                                                      |\n"
             << "|                                               WRITE MENU TO GO TO THE MAIN MENU                                                |\n"
             << "|________________________________________________________________________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> input;
            if (isNumerical(input) && page * 20 <= stoi(input) && stoi(input) <= min(page * 20 + 20, (int) cities.size())) {
                alive = cityInfo(citiesCache[stoi(input)]);
                break;
            } else if (normalise(input) == "w" && page * 20 - 20 >= 0) {
                page--;
                break;
            } else if (normalise(input) == "s" && page * 20 + 20 < (int) cities.size()) {
                page++;
                break;
            } else if (normalise(input) == "menu")
                return;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
}

bool Menu::cityInfo(City *city) {
    bool alive = true;

    while (alive) {
        cleanTerminal();
        string header = city->getName();
        cout << "__________________________________________________________________________________________________________________________________\n"
             << "|" << setw(65 + (int) header.size() / 2) << right << header << setw(65 - (int) header.size() / 2) << right << " |\n"
             << "|                                                      SELECT AN AIRPORT                                                         |\n"
             << "|________________________________________________________________________________________________________________________________|\n";
        for (int i = 0; i < city->getAirports().size(); i++) {
            cout << right << setw(20) << to_string(i + 1) + ".   " << left << setw(30)
                 << city->getAirports()[i]->getCode() + " " + city->getAirports()[i]->getName() << endl;
        }
        cout << "__________________________________________________________________________________________________________________________________\n"
             << "|                                                       WRITE W TO MOVE UP                                                       |\n"
             << "|                                                      WRITE S TO MOVE DOWN                                                      |\n"
             << "|                                             WRITE BACK TO GO TO THE PREVIOUS MENU                                              |\n"
             << "|                                               WRITE MENU TO GO TO THE MAIN MENU                                                |\n"
             << "|________________________________________________________________________________________________________________________________|\n\n";
        while (true) {

            cout << "   - OPTION: ";
            cin >> input;
            if (isNumerical(input) && 1 <= stoi(input) && stoi(input) <= city->getAirports().size()) {
                while (true) {
                    cout << "   - 1. Display airport info" << endl
                         << "   - 2. Display possible targets" << endl;
                    cin >> input;
                    if (input == "1")
                        alive = airportInfo(city->getAirports()[stoi(input) - 1]);
                    if (input == "2")
                        alive = reachableAirports(city->getAirports()[stoi(input) - 1]);
                    break;
                }
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

void Menu::fastSearchMenu() {
    cleanTerminal();
    Airport *source = nullptr;
    Airport *target = nullptr;
    bool alive = true;

    while (alive) {
        cleanTerminal();
        cout << "__________________________________________________________________________________________________________________________________\n"
             << "|                                                        Fast search menu                                                        |\n"
             << "|                                Write the code of two airports to be your source and destination                                |\n"
             << "|________________________________________________________________________________________________________________________________|\n\n\n\n";
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




