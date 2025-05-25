#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include <vector>
#include <string>
#include "../algorithms/common.h"

/**
 * @file brute_force.h
 * @brief Declaração da função de força bruta para seleção de pallets.
 * @brief [EN] Declaration of brute-force function for pallet selection.
 *
 * Este cabeçalho contém a declaração da função que implementa uma abordagem de força bruta
 * para resolver o problema de carregamento de pallets em um caminhão.
 *
 * [EN] This header contains the declaration of the function that implements a brute-force
 * approach to solve the pallet loading problem for a truck.
 */

/**
 * @brief Resolve o problema de seleção de pallets para um caminhão usando força bruta.
 * @brief [EN] Solves the pallet selection problem for a truck using brute force.
 *
 * Esta função tenta todas as combinações possíveis de pallets para encontrar o conjunto
 * com o maior lucro possível que não ultrapasse a capacidade do caminhão.
 * A execução é interrompida se exceder o tempo limite.
 *
 * [EN] This function tests all possible combinations of pallets to find the subset
 * with the highest profit that does not exceed the truck's weight capacity.
 * Execution is interrupted if it exceeds the time limit.
 *
 * @param pallets Vetor de pallets disponíveis, cada um com peso e lucro.
 * [EN] Vector of available pallets, each with weight and profit.
 *
 * @param truck Caminhão com capacidade máxima de carga.
 * [EN] Truck with maximum weight capacity.
 *
 * @return Solution Resultado da execução: pallets selecionados, lucro total,
 * tempo de execução, nome do algoritmo e se foi interrompido por tempo.
 * [EN] Result of the execution: selected pallets, total profit, execution time,
 * algorithm name, and whether it was terminated due to time limit.
 */
Solution solveBruteForce(const std::vector<Pallet>& pallets, const Truck& truck);

#endif // BRUTE_FORCE_H
