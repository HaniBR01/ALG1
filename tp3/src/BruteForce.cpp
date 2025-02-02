#include "Grafo.hpp"

//codigo adaptado do geeks for geeks

std::pair<int, std::vector<int>> Grafo::tspBruteForce() {
    
    auto start = std::chrono::high_resolution_clock::now();

    int numNodes = int(matriz.size());
    std::vector<int> nodes;
    for (int i = 1; i < numNodes; i++)
        nodes.push_back(i);

    int minCost = std::numeric_limits<int>::max();
    std::vector<int> bestPath;
    permute(nodes, 0, int(nodes.size() - 1), minCost, bestPath);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    printFile(duration,"BruteForce.csv");

    return {minCost, bestPath};
}

void Grafo::permute(std::vector<int> &nodes, int l, int r, int &minCost, std::vector<int> &bestPath) {
    if (l == r) {
        int currCost = 0, currNode = 0;
        std::vector<int> path = {0};
        for (int i = 0; i < int(nodes.size()); i++) {
            currCost += matriz[currNode][nodes[i]];
            currNode = nodes[i];
            path.push_back(currNode);
        }
        currCost += matriz[currNode][0];
        path.push_back(0);
        if (currCost < minCost) {
            minCost = currCost;
            bestPath = path;
        }
        return;
    }
    
    for (int i = l; i <= r; i++) {
        std::swap(nodes[l], nodes[i]);
        permute(nodes, l + 1, r, minCost, bestPath);
        std::swap(nodes[l], nodes[i]);
    }
}