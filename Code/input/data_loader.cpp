#include "data_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>

DataLoader::DataLoader() {}

bool DataLoader::loadTruckData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::string line;
    // Skip header line
    std::getline(file, line);

    // Read truck data (only one truck per dataset)
    if (std::getline(file, line)) {
        return parseTruckLine(line, truck);
    }

    return false;
}

bool DataLoader::loadPalletData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::string line;
    // Skip header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        Pallet pallet;
        if (parsePalletLine(line, pallet)) {
            pallets.push_back(pallet);
        }
    }

    return !pallets.empty();
}

bool DataLoader::parsePalletLine(const std::string& line, Pallet& pallet) {
    std::stringstream ss(line);
    std::string item;
    
    try {
        // Parse ID
        std::getline(ss, item, ',');
        pallet.id = std::stoi(item);
        
        // Parse weight
        std::getline(ss, item, ',');
        pallet.weight = std::stod(item);
        
        // Parse profit
        std::getline(ss, item, ',');
        pallet.profit = std::stod(item);

        pallet.weightProfitRatio = pallet.weight > 0 ? pallet.profit / pallet.weight : 0.0;
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error parsing pallet line: " << e.what() << std::endl;
        return false;
    }
}

bool DataLoader::parseTruckLine(const std::string& line, Truck& truck) {
    std::stringstream ss(line);
    std::string item;
    
    try {
        // Parse capacity
        std::getline(ss, item, ',');
        truck.capacity = std::stod(item);
        
        // Parse max pallets
        std::getline(ss, item, ',');
        truck.maxPallets = std::stoi(item);
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error parsing truck line: " << e.what() << std::endl;
        return false;
    }
}

void DataLoader::clear() {
    pallets.clear();
    // Reset truck to default values
    truck = Truck();
} 