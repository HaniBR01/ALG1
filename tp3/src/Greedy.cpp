#include "Grafo.hpp"

std::pair<int, std::vector<int>> Grafo::tspGreedy() {
    
    auto start = std::chrono::high_resolution_clock::now();

    auto tsp = matriz;
    int sum = 0;
    int counter = 0;
    int j = 0, i = 0;
    int min = std::numeric_limits<int>::max();
    std::unordered_map<int, int> visitedRouteList;
    std::vector<int> route;

    visitedRouteList[0] = 1;
    route.push_back(0);

    while (counter < int(tsp.size()) - 1) {
        min = std::numeric_limits<int>::max();
        int nextCity = -1;

        for (j = 0; j < int(tsp.size()); j++) {
            if (i != j && visitedRouteList[j] == 0 && tsp[i][j] < min) {
                min = tsp[i][j];
                nextCity = j;
            }
        }

        if (nextCity == -1) {
            return {-1, {}}; // Caminho inválido
        }

        sum += min;
        visitedRouteList[nextCity] = 1;
        route.push_back(nextCity);
        i = nextCity;
        counter++;
    }

    // Retornando ao ponto inicial
    sum += tsp[i][0];
    route.push_back(0);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    printFile(duration,"Greedy.csv");

    return {sum, route};
}