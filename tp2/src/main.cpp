#include "Grafo.hpp"
#include "NetworkAnalysis.hpp"
#include <iostream>
#include <fstream>

int main() {
    int vertices, Arestas;
    std::cin >> vertices >> Arestas;

    Grafo Grafo(vertices);

    for (int i = 0; i < Arestas; ++i) {
        int from, to, capacity;
        std::cin >> from >> to >> capacity;
        Grafo.addAresta(from - 1, to - 1, capacity);
    }

    return 0;
}
