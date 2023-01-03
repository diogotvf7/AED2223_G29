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
    status = 0;
    ui = "";
}

void Menu::run() {

    bool alive = true;
    while (alive) {
        switch (status) {

            case 0: // Main menu
                status = mainMenu();
                break;
            case 5: // EXIT
                cleanTerminal();
                alive = false;
                break;
        }
        cleanTerminal();
    }
}

int Menu::mainMenu() {
    cleanTerminal();
    cout << "__________________________________________________________________\n"
         << "|                           Main menu                            |\n"
         << "|                  Choose an option to continue                  |\n"
         << "|________________________________________________________________|\n"
         << "|                                                                |\n"
         << "|                  1. SEE AIRPORTS                               |\n"
         << "|                  2. SEE AIRLINES                               |\n"
         << "|                  3. SEE COUNTRIES                              |\n"
         << "|                  4. SEE CITIES                                 |\n"
         << "|                  5. EXIT                                       |\n"
         << "|________________________________________________________________|\n\n";

    while (true) {
        cout << "   - OPTION: "; cin >> ui;
        if ("1" <= ui && ui <= "5") return stoi(ui);
        else cout << "   - INVALID OPTION" << endl;
    }
}

void Menu::cleanTerminal() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}
