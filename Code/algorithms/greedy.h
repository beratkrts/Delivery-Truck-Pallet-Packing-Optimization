#ifndef GREEDY_H
#define GREEDY_H

#include "common.h"

/**
 * @file greedy.h
 * @brief Declaração da função que implementa o algoritmo guloso.
 * @brief [EN] Declaration of the function that implements the greedy algorithm.
 *
 * Este cabeçalho declara a função que resolve o problema de seleção de pallets
 * utilizando uma abordagem gulosa (greedy).
 *
 * [EN] This header declares the function that solves the pallet selection problem
 * using a greedy approach.
 */

/**
 * @brief Resolve o problema de seleção de pallets usando algoritmo guloso.
 * @brief [EN] Solves the pallet selection problem using greedy algorithm.
 *
 * Esta função utiliza uma abordagem gulosa para selecionar os pallets que
 * maximizam o lucro sem ultrapassar a capacidade do caminhão. O algoritmo
 * guloso toma decisões localmente ótimas em cada etapa.
 *
 * [EN] This function uses a greedy approach to select the pallets that
 * maximize profit without exceeding the truck's capacity. The greedy algorithm
 * makes locally optimal decisions at each step.
 *
 * @param pallets Vetor contendo os pallets disponíveis.
 * [EN] Vector containing the available pallets.
 *
 * @param truck Caminhão com capacidade de carga.
 * [EN] Truck with load capacity.
 *
 * @return Solution Objeto contendo os pallets selecionados, lucro total e estatísticas da execução.
 * [EN] Object containing selected pallets, total profit, and execution statistics.
 */
Solution solveGreedy(const std::vector<Pallet>& pallets, const Truck& truck);

#endif // GREEDY_H