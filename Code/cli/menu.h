#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include "../algorithms/common.h"

class Menu {
public:
    Menu();
    void run();

private:
    void displayMainMenu();
    void loadData();
    void runAlgorithm();
    void displayResults();
    void saveResults();
    void exitProgram();

    std::vector<Pallet> pallets;
    std::vector<Truck> trucks;
    Solution currentSolution;
    bool dataLoaded;
};

#endif // MENU_H 