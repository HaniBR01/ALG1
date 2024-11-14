#ifndef ESTADO_HPP
#define ESTADO_HPP

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "grafo.hpp"

using namespace std;

class Estado{
    public:
        Grafo Imperio;
        int centros;
        int estradas;
        string capital;
    public:
        Estado (int n, int m);
        string encontrarCapital();
        bool encontrarCapital(const std::vector<std::string>& componente, const std::string& capital) const;
        pair<int, vector<string>> kosaraju();
        vector<pair<string, vector<string>>> realizarPatrulhamento();
};

#endif