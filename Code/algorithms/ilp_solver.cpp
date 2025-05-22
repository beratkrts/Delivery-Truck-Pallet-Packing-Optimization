#include "ilp_solver.h"
#include "ortools/linear_solver/linear_solver.h"
using namespace operations_research;

Solution solveILP(const std::vector<Pallet>& pallets, const Truck& truck) {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution;
    solution.truck = truck;
    solution.algorithmName = "Integer Linear Programming";
    // TODO: Implement ILP solver algorithm
    MPSolver solver("KnapsackILP", MPSolver::CBC_MIXED_INTEGER_PROGRAMMING);
    int n = pallets.size();
    std::vector<MPVariable*> x(n);

    for (int i = 0; i < n; i++) {
        x[i] = solver.MakeIntVar(0, 1, "x" + std::to_string(i));
    }
    //Capacity constraint
    MPConstraint* ct1 = solver.MakeRowConstraint(0, truck.capacity);
    for (int i = 0; i < n; ++i) {
        ct1->SetCoefficient(x[i], pallets[i].weight);
    }
    //Max Pallets Constraint
    MPConstraint* ct2 = solver.MakeRowConstraint(0, truck.maxPallets);
    for (int i = 0; i < n; ++i) {
        ct2->SetCoefficient(x[i], 1);
    }

    //Objective
    MPObjective* objective= solver.MutableObjective();
    for (int i = 0; i < n; ++i) {
        objective->SetCoefficient(x[i], pallets[i].profit);
    }
    objective->SetMaximization();

    if (solver.Solve() == MPSolver::OPTIMAL) {
        solution.totalProfit = static_cast<int>(objective->Value());
        for (int i = 0; i < n; ++i) {
            if (x[i]->solution_value() > 0.5) {
                solution.selectedPallets.push_back(pallets[i]);
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    solution.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    return solution;
} 