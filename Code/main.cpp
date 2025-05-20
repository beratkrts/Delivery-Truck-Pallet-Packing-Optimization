#include <iostream>
#include "cli/menu.h"
#include "input/data_loader.h"
#include "algorithms/common.h"
#include "utils/timer.h"

int main(int argc, char* argv[]) {
    try {
        // Initialize the menu system
        Menu menu;
        
        // Start the main program loop
        menu.run();
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
} 