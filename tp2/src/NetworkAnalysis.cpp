#include "NetworkAnalysis.hpp"

NetworkAnalysis::NetworkAnalysis(Grafo& Grafo) : Grafo(Grafo) {}

int NetworkAnalysis::getTotalCapacity() {
    int totalCapacity = 0;
    const auto& adjList = Grafo.getAdjList();
    for (size_t i = 0; i < adjList.size(); ++i) {
        for (const auto& Aresta : adjList[i]) {
            totalCapacity += Aresta.capacity;
        }
    }
    return totalCapacity;
}

int NetworkAnalysis::getUnmetDemand() {
    auto demands = Grafo.getConsumerDemands();
    auto generatorFlows = Grafo.getGeneratorFlows();

    int totalDemand = 0;
    int totalFlow = 0;

    for (const auto& [consumer, demand] : demands) {
        totalDemand += demand;
    }

    for (const auto& [generator, flow] : generatorFlows) {
        totalFlow += flow;
    }

    return totalDemand - totalFlow;
}

int NetworkAnalysis::getLostEnergy() {
    int totalLostEnergy = 0;
    const auto& adjList = Grafo.getAdjList();
    for (size_t i = 0; i < adjList.size(); ++i) {
        for (const auto& Aresta : adjList[i]) {
            if (Aresta.flow > Aresta.capacity) {
                totalLostEnergy += Aresta.flow - Aresta.capacity;
            }
        }
    }
    return totalLostEnergy;
}

std::vector<std::tuple<int, int, int>> NetworkAnalysis::getCriticalConnections() {
    std::vector<std::tuple<int, int, int>> criticalConnections;
    const auto& adjList = Grafo.getAdjList();
    for (size_t i = 0; i < adjList.size(); ++i) {
        for (const auto& Aresta : adjList[i]) {
            if (Aresta.flow == Aresta.capacity) {
                criticalConnections.emplace_back(i, Aresta.to, Aresta.capacity);
            }
        }
    }
    return criticalConnections;
}