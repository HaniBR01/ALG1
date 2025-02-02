#include "Grafo.hpp"
#include <iostream>
#include <fstream>


int main() {
    int vertices, arestas;
    char c;
    std::cin >> c >> vertices >> arestas;
    Grafo g(vertices, arestas);
    if(c == 'b'){
        g.print(g.tspBruteForce());
    }else if(c == 'd'){
        g.print(g.tspDynamic());
    }else if(c == 'g'){
        g.print(g.tspGreedy());
    }

    return 0;
}
