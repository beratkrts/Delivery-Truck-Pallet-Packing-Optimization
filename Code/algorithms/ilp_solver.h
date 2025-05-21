#ifndef ILP_SOLVER_H
#define ILP_SOLVER_H

#include "common.h"

// Integer Linear Programming solver implementation
Solution solveILP(const std::vector<Pallet>& pallets, const Truck& truck);

#endif // ILP_SOLVER_H 