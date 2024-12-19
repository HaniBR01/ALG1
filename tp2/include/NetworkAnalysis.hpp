#ifndef NETWORK_ANALYSIS_HPP
#define NETWORK_ANALYSIS_HPP

#include "Grafo.hpp"
#include <vector>
#include <tuple>

class NetworkAnalysis {
public:
    NetworkAnalysis(Grafo& Grafo);

    int getTotalCapacity();
    int getUnmetDemand();
    int getLostEnergy();
    std::vector<std::tuple<int, int, int>> getCriticalConnections();

private:
    Grafo& Grafo;
};

#endif