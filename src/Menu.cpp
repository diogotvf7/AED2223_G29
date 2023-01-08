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

bool isNumerical(const string &s) {
    for (char c : s)
        if (!isdigit(c)) return false;
    return true;
}

bool isAlpha(const string &s) {
    for (char c : s)
        if (!isalpha(c)) return false;
    return true;
}

bool isCoordinate(const string &s) {
    return regex_match(s, regex("^[-+]?([1-8]?\\d(\\.\\d+)?|90(\\.0+)?),\\s*[-+]?(180(\\.0+)?|((1[0-7]\\d)|([1-9]?\\d))(\\.\\d+)?)$"));
}

Coordinate getCoordinate(const string &s) {
    stringstream tmp(s); string latitude, longitude;
    getline(tmp, latitude, ',');
    getline(tmp, longitude);
    return {stod(latitude), stod(longitude)};
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
            case 2:
                input= "0";
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
             << "|                                              WRITE A NUMBER TO SELECT AN AIRPORT                                               |\n"
             << "|                                           WRITE AN AIRPORT CODE TO SELECT AN AIRPORT                                           |\n"
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
                    else if (input == "2")
                         alive = reachableAirports(airportsCache[stoi(tmp) - 1]);
                    else cout << "   - INVALID OPTION" << endl;
                    break;
                }
                break;
            } else if (isAlpha(input) && input.size() == 3) {
                if (dm->getAirports().find(input) == dm->getAirports().end()) cout << "   - WRONG CODE\n";
                else {
                    while (true) {
                        cout << "   - 1. Display airport info" << endl
                             << "   - 2. Display possible targets" << endl;
                        cin >> input;
                        if (input == "1")
                            alive = airportInfo(dm->getAirports()[tmp]);
                        else if (input == "2")
                            alive = reachableAirports(dm->getAirports()[tmp]);
                        else cout << "   - INVALID OPTION" << endl;
                        break;
                    }
                    break;
                }
            } else if (normalise(input) == "w" && page * 20 - 20 >= 0) {
                page--;
                break;
            } else if (normalise(input) == "s" && page * 20 + 20 < (int) airport.size()) {
                page++;
                break;
            } else if (normalise(input) == "menu" || normalise(input) == "back")
                return;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
}

bool Menu::airportInfo(Airport *source) {
    bool alive = true;
    int page = 0;
    int separator = 0, gap = 3;
    unordered_set<string> targets = dm->getFlightsGraph()->airportsInNFlights(source->getCode(), gap);
    auto itr = targets.begin();
    vector<string> cache;
    while (alive) {
        cleanTerminal();
        string header = source->getCode() + "   " + source->getName();
        cout << "__________________________________________________________________________________________________________________________________\n"
             << "|" << setw(65 + (int) header.size() / 2) << right << header << setw(65 - (int) header.size() / 2) << right << " |\n";
        if (separator == 0) cout << "|                                     DISPLAYING POSSIBLE TARGET AIRPORTS IN " << setw(2) << left << gap << " FLIGHTS                                          |\n";
        if (separator == 1) cout << "|                                    DISPLAYING POSSIBLE TARGET COUNTRIES IN " << setw(2) << left << gap << " FLIGHTS                                          |\n";
        if (separator == 2) cout << "|                                       DISPLAYING POSSIBLE TARGET CITIES IN " << setw(2) << left << gap << " FLIGHTS                                          |\n";
        if (separator == 3) cout << "|                                          DISPLAYING POSSIBLE AIRLINES IN " << setw(2) << left << gap << " FLIGHTS                                            |\n";
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
        if (separator == 0)
            cout << "|                                                WRITE A NUMBER TO GO TO FLIGHT MENU                                             |\n";
        if (separator == 1)
            cout << "|                                                WRITE A NUMBER TO GO TO COUNTRY MENU                                            |\n";
        if (separator == 2)
            cout << "|                                                 WRITE A NUMBER TO GO TO CITY MENU                                              |\n";
        cout << "|                                                 WRITE W OR S TO MOVE UP OR DOWN                                                |\n";
        if (separator == 0) cout << "|                                                   WRITE D TO GO TO NEXT MODE                                                   |\n";
        else if (separator == 1 || separator == 2) cout << "|                                           WRITE A OR D TO GO TO PREVIOUS OR NEXT MODE                                          |\n";
        else if (separator == 3) cout << "|                                                 WRITE A TO GO TO PREVIOUS MODE                                                 |\n";
        if (gap == 1) cout << "|                                                WRITE U TO INCREASE MAX FLIGHTS                                                |\n";
        if (1 < gap && gap < 9) cout << "|                                        WRITE U OR J TO INCREASE OR DECREASE MAX FLIGHTS                                        |\n";
        if (gap == 9) cout << "|                                                WRITE J TO DECREASE MAX FLIGHTS                                                |\n";
        cout << "|                                             WRITE BACK TO GO TO THE PREVIOUS MENU                                              |\n"
             << "|                                               WRITE MENU TO GO TO THE MAIN MENU                                                |\n"
             << "|________________________________________________________________________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> input;
            if (separator < 3 && isNumerical(input) && page * 20 + 1 <= stoi(input) && stoi(input) <= min(page * 20 + 20, (int) targets.size() - 1)) {
                if (separator == 0)
                    alive = flightInfo(source, dm->getAirports()[cache[stoi(input) - 1]]);
                else if (separator == 1)
                    alive = countryInfo(dm->getCountries()[cache[stoi(input) - 1]]);
                else if (separator == 2)
                    alive = cityInfo(dm->getCities()[cache[stoi(input) - 1]]);
                break;
            } else if (normalise(input) == "w" && page * 20 - 20 >= 0) {
                page--;
                break;
            } else if (normalise(input) == "s" && page * 20 + 20 < (int) targets.size() - 1) {
                page++;
                break;
            } else if (normalise(input) == "a" && separator > 0) {
                page = 0;
                if (separator == 1) targets = dm->getFlightsGraph()->airportsInNFlights(source->getCode(), gap);
                if (separator == 2) targets = dm->getFlightsGraph()->countriesInNFlights(source->getCode(), gap);
                if (separator == 3) targets = dm->getFlightsGraph()->citiesInNFlights(source->getCode(), gap);
                itr = targets.begin(); cache.clear(); separator--;
                break;
            } else if (normalise(input) == "d" && separator < 3) {
                page = 0;
                if (separator == 0) targets = dm->getFlightsGraph()->countriesInNFlights(source->getCode(), gap);
                if (separator == 1) targets = dm->getFlightsGraph()->citiesInNFlights(source->getCode(), gap);
                if (separator == 2) targets = dm->getFlightsGraph()->airlinesInNFlights(source->getCode(), gap);
                itr = targets.begin(); cache.clear(); separator++;
                break;
            } else if (normalise(input) == "u" && 1 <= gap && gap < 9) {
                page = 0; gap++;
                if (separator == 0) targets = dm->getFlightsGraph()->airportsInNFlights(source->getCode(), gap);
                if (separator == 1) targets = dm->getFlightsGraph()->countriesInNFlights(source->getCode(), gap);
                if (separator == 2) targets = dm->getFlightsGraph()->citiesInNFlights(source->getCode(), gap);
                if (separator == 3) targets = dm->getFlightsGraph()->airlinesInNFlights(source->getCode(), gap);
                itr = targets.begin(); cache.clear();
                break;
            } else if (normalise(input) == "j" && 1 < gap && gap <= 9) {
                page = 0; gap--;
                if (separator == 0) targets = dm->getFlightsGraph()->airportsInNFlights(source->getCode(), gap);
                if (separator == 1) targets = dm->getFlightsGraph()->countriesInNFlights(source->getCode(), gap);
                if (separator == 2) targets = dm->getFlightsGraph()->citiesInNFlights(source->getCode(), gap);
                if (separator == 3) targets = dm->getFlightsGraph()->airlinesInNFlights(source->getCode(), gap);
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
        if (targets.size() > 1)
            for (int i = page * 20 + 1; i <= min(page * 20 + 20, (int) targets.size() - 1); i++) {
                cout << right << setw(20) << to_string(i) + ".   " << left << setw(30)
                     << airports[targets[i]]->getCode() + " " + airports[targets[i]]->getName();
                cout << endl;
            }
        else
            cout << "                                         There are no possible destinations from this airport!                                  " << endl;
        cout << "__________________________________________________________________________________________________________________________________\n";
        if (targets.size() > 1)
            cout << "|                                              WRITE A NUMBER TO SELECT AN AIRPORT                                               |\n"
                 << "|                                           WRITE AN AIRPORT CODE TO SELECT AN AIRPORT                                           |\n"
                 << "|                                                       WRITE W TO MOVE UP                                                       |\n"
                 << "|                                                      WRITE S TO MOVE DOWN                                                      |\n";
        cout << "|                                             WRITE BACK TO GO TO THE PREVIOUS MENU                                              |\n"
             << "|                                               WRITE MENU TO GO TO THE MAIN MENU                                                |\n"
             << "|________________________________________________________________________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> input;
            if (isNumerical(input) && page * 20 + 1 <= stoi(input) && stoi(input) <= min(page * 20 + 20, (int) targets.size() - 1)) {
                alive = flightInfo(source, airports[targets[stoi(input)]]);
                break;
            } else if (targets.size() > 1 && isAlpha(input) && input.size() == 3) {
                // if (dm->getAirports().find(input) == dm->getAirports().end()) cout << "   - WRONG CODE";
                if (find(targets.begin(), targets.end(), input) == targets.end()) cout << "   - WRONG CODE";
                else alive = flightInfo(source, dm->getAirports()[input]);
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
    if (source == nullptr || target == nullptr) {
        cout << "There was some problem with the flight you searched for.\nTry to change some values.\n";
        cout << "WRITE SOMETHING TO GO BACK"; string _; cin >> _;
        return true;
    }
    double minDistance = dm->getFlightsGraph()->minDistanceCodeCode(source->getCode(), target->getCode(), false);
    list<Airport*> minDistancePath = dm->getFlightsGraph()->path(source, target);
    double minNumberFlights = dm->getFlightsGraph()->minDistanceCodeCode(source->getCode(), target->getCode(), true);
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
        if (minNumberFlights == -1)
            cout << "                               IT IS IMPOSSIBLE TO GET TO THE TARGET AIRPORT FROM THE SOURCE AIRPORT                           " << endl;
        else {
            cout << right << setw(20) << "Minimum distance: " << minDistance << " km;" << endl;
            auto itr1 = minDistancePath.begin();
            int counter1 = 1;
            while (itr1 != minDistancePath.end()) {
                cout << right << setw(7) << counter1++ << ": " << (*itr1)->getCode() << ' ' << (*itr1++)->getName()
                     << endl;
            }
            cout
                    << "__________________________________________________________________________________________________________________________________\n";
            cout << right << setw(20) << "Minimum number of flights: " << minNumberFlights << " flights;" << endl;
            auto itr2 = minNumberFlightsPath.begin();
            int counter2 = 1;
            while (itr2 != minNumberFlightsPath.end()) {
                cout << right << setw(7) << counter2++ << ": " << (*itr2)->getCode() << ' ' << (*itr2++)->getName()
                     << endl;
            }
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
    int separator = 0;
    while (alive) {
        cleanTerminal();
        string header = country->getName();
        cout << "__________________________________________________________________________________________________________________________________\n"
             << "|" << setw(65 + (int) header.size() / 2) << right << header << setw(65 - (int) header.size() / 2) << right << " |\n";
        if (separator == 0) cout << "|                                                      DISPLAYING CITIES                                                         |\n";
        else if (separator == 1) cout << "|                                                     DISPLAYING AIRLINES                                                        |\n";
        else if (separator == 2) cout << "|                                                     DISPLAYING AIRPORTS                                                        |\n";
        cout << "|________________________________________________________________________________________________________________________________|\n";

        int maxIndex = (int) cities.size() * (separator == 0) + (int) airlines.size() * (separator == 1) + (int) airports.size() * (separator == 2);
        for (int i = page * 20; i < min(page * 20 + 20, maxIndex); i++) {
            if (separator == 0)
                cout << right << setw(20) << to_string(i + 1) + ".   " << right << setw(30)
                     << cities[i]->getName() << " : " << cities[i]->getAirports().size() << " airports;" << endl;
            else if (separator == 1)
                cout << right << setw(30) << to_string(i + 1) + ".   " << left << setw(30)
                     << airlines[i]->getName() << endl;
            else if (separator == 2)
                cout << right << setw(5) << to_string(i + 1) + ".   " << left << setw(30)
                     << airports[i]->getCode() << ' ' << setw(60) << left << airports[i]->getName() << airports[i]->getCoordinate() << endl;

        }
        cout << "__________________________________________________________________________________________________________________________________\n";
        if (separator == 0)
            cout << "|                                                WRITE A NUMBER TO GO TO CITY MENU                                               |\n";
        if (separator == 2)
            cout << "|                                               WRITE A NUMBER TO GO TO AIRPORT MENU                                             |\n";
        cout << "|                                                 WRITE W OR S TO MOVE UP OR DOWN                                                |\n";
        if (separator == 0) cout << "|                                                   WRITE D TO GO TO NEXT MODE                                                   |\n";
        if (separator == 1) cout << "|                                           WRITE A OR D TO GO TO PREVIOUS OR NEXT MODE                                          |\n";
        if (separator == 2) cout << "|                                                 WRITE A TO GO TO PREVIOUS MODE                                                 |\n";
        cout << "|                                             WRITE BACK TO GO TO THE PREVIOUS MENU                                              |\n"
             << "|                                               WRITE MENU TO GO TO THE MAIN MENU                                                |\n"
             << "|________________________________________________________________________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> input;
            if ((separator == 0 || separator == 2) && isNumerical(input) && page * 21 <= stoi(input) && stoi(input) <= min(page * 20 + 20, maxIndex)) {
                if (separator == 0)
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
            } else if (normalise(input) == "a" && separator > 0) {
                page = 0;
                if (separator == 2 && airlines.empty()) separator--;
                separator--;
                break;
            } else if (normalise(input) == "d" && separator < 2) {
                page = 0;
                if (separator == 0 && airlines.empty()) separator++;
                separator++;
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
            string tmp = input;
            if (isNumerical(input) && 1 <= stoi(input) && stoi(input) <= city->getAirports().size()) {
                while (true) {
                    cout << "   - 1. Display airport info" << endl
                         << "   - 2. Display possible targets" << endl;
                    cin >> input;
                    if (input == "1")
                        alive = airportInfo(city->getAirports()[stoi(tmp) - 1]);
                    if (input == "2")
                        alive = reachableAirports(city->getAirports()[stoi(tmp) - 1]);
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
    Airport *sourceCode = nullptr;
    Airport *targetCode = nullptr;
    Coordinate sourceCoordinate;
    Coordinate targetCoordinate;
    Country *sourceCountry = nullptr;
    Country *targetCountry = nullptr;
    City *sourceCity = nullptr;
    City *targetCity = nullptr;
    bool alive = true;

    while (alive) {
        cleanTerminal();
        cout << "__________________________________________________________________________________________________________________________________\n"
             << "|                                                        Fast search menu                                                        |\n"
             << "|################################################################################################################################|\n"
             << "|################################################################################################################################|\n"
             << "|#   0. CODE - CODE             ##   1. COORDINATE - CODE       ##   2. CITY - CODE             ##   3. COUNTRY - CODE          #|\n"
             << "|#   4. CODE - COORDINATE       ##   5. COORDINATE - COORDINATE ##   6. CITY - COORDINATE       ##   7. COUNTRY - COORDINATE    #|\n"
             << "|#   8. CODE - CITY             ##   9. COORDINATE - CITY       ##  10. CITY - CITY             ##  11. COUNTRY - CITY          #|\n"
             << "|#  12. CODE - COUNTRY          ##  13. COORDINATE - COUNTRY    ##  14. CITY - COUNTRY          ##  15. COUNTRY - COUNTRY       #|\n"
             << "|################################################################################################################################|\n"
             << "| COORDINATE EXAMPLE - '1.0000000,-12.0000000'                                                      16. EXIT                     |\n"
             << "|________________________________________________________________________________________________________________________________|\n\n\n\n";
        int option, radius; bool mode;
        while (true) {
            cout << "   - OPTION: ";
            cin >> input;
            if (isNumerical(input) && 0 <= stoi(input) && stoi(input) <= 16) {
                option = stoi(input);
                break;
            }
            else cout << "   - INVALID OPTION" << endl;
        }
        if (input == "16") break;
        while (true) {
            cout << "     Choose your preference:" << endl
                 << "   - 1. Minimum number of flights" << endl
                 << "   - 2. Minimum distance" << endl;
            cout << "   :"; cin >> input;
            if (input == "1") {mode = true; break;}
            else if (input == "2") {mode = false; break;}
            else cout << "   - INVALID OPTION" << endl;
        }
        if (option % 4 == 1 || option / 4 == 1)
            while (true) {
                cout << "     Insert a radius (integer in km): ";
                cin >> input;
                if (isNumerical(input)) {
                    radius = stoi(input);
                    break;
                }
                else cout << "   - INVALID OPTION" << endl;

            }
        while (true) {

            cout << right << setw(20) << "Source: "; getline(cin >> ws, input); cout << endl;
            if (option % 4 == 0 && dm->getAirports().find(input) != dm->getAirports().end()) {
                sourceCode = dm->getAirports()[input];
                break;
            }
            if (option % 4 == 1 && isCoordinate(input)) {
                sourceCoordinate = getCoordinate(input);
                break;
            }
            if (option % 4 == 2 && dm->getCities().find(input) != dm->getCities().end()) {
                sourceCity = dm->getCities()[input];
                break;
            }
            if (option % 4 == 3 && dm->getCountries().find(input) != dm->getCountries().end()) {
                sourceCountry = dm->getCountries()[input];
                break;
            }
            else cout << right << setw(20) << "Invalid input!\n";
        }
        while (true) {
            cout << right << setw(20) << "Target: "; getline(cin >> ws, input); cout << endl;
            if (option / 4 == 0 && dm->getAirports().find(input) != dm->getAirports().end()) {
                targetCode = dm->getAirports()[input];
                break;
            }
            if (option / 4 == 1 && isCoordinate(input)) {
                targetCoordinate = getCoordinate(input);
                break;
            }
            if (option / 4 == 2 && dm->getCities().find(input) != dm->getCities().end()) {
                targetCity = dm->getCities()[input];
                break;
            }
            if (option / 4 == 3 && dm->getCountries().find(input) != dm->getCountries().end()) {
                targetCountry = dm->getCountries()[input];
                break;
            }
            else cout << right << setw(20) << "Invalid input!\n";
        }

        switch (option) {
            case 0: {
                alive = flightInfo(sourceCode, targetCode);
                break;
            }
            case 1: {
                auto p = dm->getFlightsGraph()->minDistanceCoordinateCode(sourceCoordinate, targetCode->getCode(), mode, radius);
                alive = flightInfo(p.first, p.second);
                break;
            }
            case 2: {
                auto p = dm->getFlightsGraph()->minDistanceCityCode(sourceCity->getName(), targetCode->getCode(), mode);
                alive = flightInfo(p.first, p.second);
                break;
            }
            case 3: {
                auto p = dm->getFlightsGraph()->minDistanceCountryCode(sourceCountry->getName(), targetCode->getCode(), mode);
                alive = flightInfo(p.first, p.second);
                break;
            }
            case 4: {
                auto p = dm->getFlightsGraph()->minDistanceCodeCoordinate(sourceCode->getCode(), targetCoordinate, mode, radius);
                alive = flightInfo(p.first, p.second);
                break;
            }
            case 5: {
                auto p = dm->getFlightsGraph()->minDistanceCoordinateCoordinate(sourceCoordinate, targetCoordinate, mode, radius);
                alive = flightInfo(p.first, p.second);
                break;
            }
            case 6: {
                auto p = dm->getFlightsGraph()->minDistanceCityCoordinate(sourceCity->getName(), targetCoordinate, mode, radius);
                alive = flightInfo(p.first, p.second);
                break;
            }
            case 7: {
                auto p = dm->getFlightsGraph()->minDistanceCountryCoordinate(sourceCountry->getName(), targetCoordinate, mode, radius);
                alive = flightInfo(p.first, p.second);
                break;
            }
            case 8: {
                auto p = dm->getFlightsGraph()->minDistanceCodeCity(sourceCode->getCode(), targetCity->getName(), mode);
                alive = flightInfo(p.first, p.second);
                break;
            }
            case 9: {
                auto p = dm->getFlightsGraph()->minDistanceCoordinateCity(sourceCoordinate, targetCity->getName(), mode, radius);
                alive = flightInfo(p.first, p.second);
                break;
            }
            case 10: {
                auto p = dm->getFlightsGraph()->minDistanceCityCity(sourceCity->getName(), targetCity->getName(), mode);
                alive = flightInfo(p.first, p.second);
                break;
            }
            case 11: {
                auto p = dm->getFlightsGraph()->minDistanceCountryCity(sourceCountry->getName(), targetCity->getName(), mode);
                alive = flightInfo(p.first, p.second);
                break;
            }
            case 12: {
                auto p = dm->getFlightsGraph()->minDistanceCodeCountry(sourceCode->getCode(), targetCountry->getName(), mode);
                alive = flightInfo(p.first, p.second);
                break;
            }
            case 13: {
                auto p = dm->getFlightsGraph()->minDistanceCoordinateCountry(sourceCoordinate, targetCountry->getName(), mode, radius);
                alive = flightInfo(p.first, p.second);
                break;
            }
            case 14: {
                auto p = dm->getFlightsGraph()->minDistanceCityCountry(sourceCity->getName(), targetCountry->getName(), mode);
                alive = flightInfo(p.first, p.second);
                break;
            }
            case 15: {
                auto p = dm->getFlightsGraph()->minDistanceCountryCountry(sourceCountry->getName(), targetCountry->getName(), mode);
                alive = flightInfo(p.first, p.second);
                break;
            }
            case 16:
                alive = false;
                break;
        }
    }
}

void Menu::cleanTerminal() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}





