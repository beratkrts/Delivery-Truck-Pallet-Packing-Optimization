#include "data_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>

DataLoader::DataLoader() {}

bool DataLoader::loadPallets(const std::string& filename) {
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

bool DataLoader::loadTrucks(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::string line;
    // Skip header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        Truck truck;
        if (parseTruckLine(line, truck)) {
            trucks.push_back(truck);
        }
    }

    return !trucks.empty();
}

bool DataLoader::parsePalletLine(const std::string& line, Pallet& pallet) {
    std::stringstream ss(line);
    std::string item;
    
    try {
        // Parse ID
        std::getline(ss, item, ',');
        pallet.id = std::stoi(item);
        
        // Parse dimensions
        std::getline(ss, item, ',');
        pallet.width = std::stod(item);
        
        std::getline(ss, item, ',');
        pallet.length = std::stod(item);
        
        std::getline(ss, item, ',');
        pallet.height = std::stod(item);
        
        // Parse weight
        std::getline(ss, item, ',');
        pallet.weight = std::stod(item);
        
        // Parse type
        std::getline(ss, pallet.type, ',');
        
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
        // Parse ID
        std::getline(ss, item, ',');
        truck.id = std::stoi(item);
        
        // Parse dimensions
        std::getline(ss, item, ',');
        truck.maxWidth = std::stod(item);
        
        std::getline(ss, item, ',');
        truck.maxLength = std::stod(item);
        
        std::getline(ss, item, ',');
        truck.maxHeight = std::stod(item);
        
        // Parse max weight
        std::getline(ss, item, ',');
        truck.maxWeight = std::stod(item);
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error parsing truck line: " << e.what() << std::endl;
        return false;
    }
}

void DataLoader::clear() {
    pallets.clear();
    trucks.clear();
} 