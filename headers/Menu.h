//
// Created by diogotvf7 on 02-01-2023.
//

#ifndef AED2223_G29_MENU_H
#define AED2223_G29_MENU_H

#include <iostream>
#include <string>

#include "DataManager.h"

class Menu {
    DataManager *dm;
    int status;
    std::string ui;

public:
    Menu(DataManager *dm);

    void run();
    int mainMenu();
    void cleanTerminal();
};


#endif //AED2223_G29_MENU_H
