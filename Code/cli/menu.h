#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <map>
#include "../algorithms/common.h"
#include "../algorithms/greedy.h"
#include "../algorithms/brute_force.h"
#include "../algorithms/dp.h"
#include "../algorithms/ilp_solver.h"
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
    void runAllAlgorithms();
    void displayResults();
    void displayAllResults();
    void saveResults();
    void clearData();
    void exitProgram();
    void displayHelp();
    
    bool validateData() const;
    void displayDatasetInfo() const;
    std::string getDatasetPath(int datasetNumber) const;
    std::string getAlgorithmName(int algorithmNumber) const;
    void displaySingleResult(const Solution& solution) const;

    std::vector<Pallet> pallets;
    Truck truck;
    std::map<int, Solution> algorithmResults;  // Store results for each algorithm
    bool dataLoaded;
    int currentDataset;
    int currentAlgorithm;
    static const int MAX_DATASETS = 10;  // Based on available datasets
    static const int MAX_ALGORITHMS = 4; // Number of available algorithms
};

#endif // MENU_H 