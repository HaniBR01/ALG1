#include "Grafo.hpp"
#include <iostream>
#include <fstream>

int main() {
    int vertices, arestas;
    std::cin >> vertices >> arestas;

    Grafo grafo(vertices, arestas);
    grafo.out();
    //std::cout << "tudo ok" << std::endl;

    return 0;
}
