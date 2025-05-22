# Delivery Truck Optimization Project

This project implements various algorithms to solve the delivery truck optimization problem, where the goal is to optimally load pallets onto trucks while respecting constraints.

## Project Structure

```
DA2025_PRJ2_G<group_number>/
├── Code/               # Source code and implementation files
├── Documentation/      # Doxygen-generated documentation
├── Presentation/      # Project presentation slides
└── datasets/          # Input data files
```

## Building the Project

1. Make sure you have the required dependencies:
   - C++ compiler (g++ or clang++)
   - Make
   - Doxygen (for documentation)
   - OR-Tools C++ library (https://developers.google.com/optimization/install/cpp)
   - On macOS
    ```bash
    brew install or-tools
    ```
2. Build the project:
   ```bash
   make
   ```

3. Generate documentation:
   ```bash
   make doc
   ```

## Running the Program

After building, run the program:
```bash
./delivery_truck_optimizer
```

## Features

- Multiple algorithm implementations:
  - Brute Force
  - Dynamic Programming
  - Greedy Algorithm
  - ILP Solver
  - Backtracking (optional)

- Input data handling from CSV files
- Performance measurement and logging
- Interactive CLI menu

## Documentation

Detailed documentation can be found in the `Documentation/html` directory. Open `index.html` in a web browser to view the documentation.

## License

This project is part of the DA2025 course assignment. 