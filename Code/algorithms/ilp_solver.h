#ifndef ILP_SOLVER_H
#define ILP_SOLVER_H

#include "common.h"

// Integer Linear Programming solver implementation
Solution solveILP(const std::vector<Pallet>& pallets, const std::vector<Truck>& trucks);

#endif // ILP_SOLVER_H 