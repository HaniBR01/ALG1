#ifndef Grafo_HPP
#define Grafo_HPP

#include <unordered_map>
#include <iostream>
#include <queue>
#include <vector>
#include <limits>
//#include <utility>
//#include <map>

typedef struct Aresta {
public:
    int destino;
    int capacidade;
    int fluxo;
    Aresta(int destino, int capacidade) : destino(destino), capacidade(capacidade), fluxo(0) {};

}Aresta;

typedef struct Vertice{
public:
    int id;
    int consumo;
    std::vector<Aresta> adjList;
    Vertice(int id, int consumo) : id(id), consumo(consumo) {};
    void addAresta(int destino, int capacidade){
        adjList.push_back(Aresta(destino, capacidade));
    }

}Vertice;


class Grafo {
public:
    Grafo(int vertices, int arestas);
    void addVertice(int id, int consumo = 0);
    void addAresta(int id, int destino, int capacidade);
    void bfs(int start);
private:
    int numVertices;
    std::unordered_map<int,Vertice> vertices;
};

    //std::map<int, int> getConsumerDemands();
    //std::map<int, int> getGeneratorFlows();
    //bool bfs(std::vector<int>& parent, int source, int sink);
#endif