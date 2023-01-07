#include <iostream>

#include "DataManager.h"
#include "Test.hpp"
#include "Statistics.hpp"
#include "Menu.h"

using namespace std;

int main() {


    int input;
    while (true) {
        cout << "0. Run menu" << endl <<
             "1. Run tests" << endl <<
             "2. Run statistics" << endl <<
             "3. Exit" << endl;
        cin >> input;
        switch (input) {
            case 0: {
                Menu menu(new DataManager("../dataset/real/"));
                menu.run();
                break;
            }
            case 1: {
                Test t;
                t.runTests();
                break;
            }
            case 2: {
                Statistics s(new DataManager("../dataset/real/"));
                s.runStatistics();
                break;
            }
            case 3: {
                return 0;
            }
        }
    }
}
