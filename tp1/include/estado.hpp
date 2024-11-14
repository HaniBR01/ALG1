#ifndef ESTADO_HPP
#define ESTADO_HPP

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "grafo.hpp"

using namespace std;

class Estado{
    private:
        Grafo Imperio;
        int centros;
        int estradas;
        
        string capital;
        vector<vector<string>> cfcs;
        vector<pair<string, vector<string>>> patrulhamentos;
        pair<int, vector<string>> batalhoes;

        void encontrarCapital();
        void kosaraju();
        void realizarPatrulhamento();
    public:
        Estado (int n, int m);
        void printCapital();
        void printCFCS();
        void printBatalhoes();
        void printPatrulhamento();
};

#endif
