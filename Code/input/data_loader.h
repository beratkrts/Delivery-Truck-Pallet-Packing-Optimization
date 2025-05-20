#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <string>
#include <vector>
#include "../algorithms/common.h"

class DataLoader {
public:
    DataLoader();
    
    // Load data from CSV files
    bool loadTruckData(const std::string& filename);
    bool loadPalletData(const std::string& filename);
    
    // Get loaded data
    const std::vector<Truck>& getTrucks() const { return trucks; }
    const std::vector<Pallet>& getPallets() const { return pallets; }
    
    // Clear loaded data
    void clear();

private:
    std::vector<Pallet> pallets;
    std::vector<Truck> trucks;
    
    // Helper functions
    bool parsePalletLine(const std::string& line, Pallet& pallet);
    bool parseTruckLine(const std::string& line, Truck& truck);
};

#endif // DATA_LOADER_H 