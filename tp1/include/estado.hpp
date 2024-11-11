#ifndef ESTADO_HPP
#define ESTADO_HPP

#include <iostream>
#include <vector>
#include <string>
#include "grafo.hpp"

using namespace std;

class Estado{
    private:
        Grafo Imperio;
        int centros;
        int estradas;
    public:
        Estado (int n, int m);
        string encontrarCapital() const;
        vector<vector<string>> kosaraju();
};

#endif