#ifndef Grafo_HPP
#define Grafo_HPP

#include <iostream>
#include <limits>
#include <map>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <queue>
#include <chrono>
#include <fstream>

class Grafo {
public:
    Grafo(int vertices, int arestas);
    std::pair<int, std::vector<int>> tspGreedy();
    std::pair<int, std::vector<int>> tspDynamic();
    std::pair<int, std::vector<int>> tspBruteForce();    
    void print(std::pair<int, std::vector<int>> vec);
private:
    //vertices do grafo
    std::vector<std::string> cidades;
    std::unordered_map<std::string,int> map;
    std::vector<std::vector<int>> matriz;

    //função de instanciação do grafo
    void printFile(std::chrono::milliseconds tempo, std::string file);
    void addVertice(std::string cidade, int indice);
    void addAresta(std::string cidade1, std::string cidade2, int capacidade);
    void permute(std::vector<int> &nodes, int l, int r, int &minCost, std::vector<int> &bestPath);
};

#endif
