#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <string>

/**
 * @struct Pallet
 * @brief Representa um pallet com peso, lucro e razão entre lucro e peso.
 * @brief [EN] Represents a pallet with weight, profit, and profit-to-weight ratio.
 */
struct Pallet {
    int id;
    /**< Identificador único do pallet.
     *  [EN] Unique identifier for the pallet.
     */

    double weight;
    /**< Peso do pallet.
     *  [EN] Weight of the pallet.
     */

    double profit;
    /**< Lucro associado ao pallet.
     *  [EN] Profit associated with the pallet.
     */

    double weightProfitRatio;
    /**< Razão lucro/peso, armazenada para otimização.
     *  [EN] Profit-to-weight ratio, stored for optimization.
     */
};

/**
 * @struct Truck
 * @brief Representa um caminhão com capacidade de carga e pallets carregados.
 * @brief [EN] Represents a truck with load capacity and loaded pallets.
 */
struct Truck {
    double capacity;
    /**< Capacidade máxima de carga do caminhão.
     *  [EN] Maximum load capacity of the truck.
     */

    std::vector<Pallet> loadedPallets;
    /**< Lista de pallets atualmente carregados.
     *  [EN] List of currently loaded pallets.
     */
};

/**
 * @struct Solution
 * @brief Armazena o resultado da execução de um algoritmo de seleção de pallets.
 * @brief [EN] Stores the result of the execution of a pallet selection algorithm.
 */
struct Solution {
    std::string algorithmName;
    /**< Nome do algoritmo utilizado.
     *  [EN] Name of the algorithm used.
     */

    Truck truck;
    /**< Caminhão utilizado na solução.
     *  [EN] Truck used in the solution.
     */

    std::vector<Pallet> selectedPallets;
    /**< Pallets selecionados pelo algoritmo.
     *  [EN] Pallets selected by the algorithm.
     */

    double totalProfit;
    /**< Lucro total obtido com os pallets selecionados.
     *  [EN] Total profit from the selected pallets.
     */

    double executionTime;
    /**< Tempo de execução do algoritmo, em segundos.
     *  [EN] Algorithm execution time, in seconds.
     */

    bool terminated;
    /**< Indica se o algoritmo foi interrompido por limite de tempo.
     *  [EN] Indicates whether the algorithm was terminated due to time limit.
     */

    double estimatedTotalTime;
    /**< Estimativa de tempo total caso o algoritmo fosse completado.
     *  [EN] Estimated total time if the algorithm were to complete.
     */
};

#endif // COMMON_H
