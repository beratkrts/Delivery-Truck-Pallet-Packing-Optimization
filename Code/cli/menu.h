#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include "../algorithms/common.h"
#include "../algorithms/greedy.h"
#include "../algorithms/brute_force.h"
#include "../algorithms/dp.h"
#include "../algorithms/ilp_solver.h"
#include "../algorithms/backtracking.h"
#include "../input/data_loader.h"

class Menu {
public:
    Menu();
    void run();

private:
    void displayMainMenu();
    void loadData();
    void selectDataset();
    void selectAlgorithm();
    void runAlgorithm();
    void displayResults();
    void saveResults();
    void clearData();
    void exitProgram();
    
    bool validateData() const;
    void displayDatasetInfo() const;
    std::string getDatasetPath(int datasetNumber) const;
    std::string getAlgorithmName(int algorithmNumber) const;

    std::vector<Pallet> pallets;
    Truck truck;
    Solution currentSolution;
    bool dataLoaded;
    int currentDataset;
    int currentAlgorithm;
    static const int MAX_DATASETS = 10;  // Based on available datasets
    static const int MAX_ALGORITHMS = 5; // Number of available algorithms
};

#endif // MENU_H 