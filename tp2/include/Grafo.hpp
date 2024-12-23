#ifndef Grafo_HPP
#define Grafo_HPP

#include <iostream>
#include <limits>
#include <map>
#include <vector>
#include <tuple>
#include <queue>

typedef struct Aresta {
public:
    int capacidade;
    int fluxo;
    Aresta(int capacidade) : capacidade(capacidade), fluxo(0) {};
    Aresta(){};
}Aresta;

typedef struct Vertice{
public:
    std::map<int,Aresta> adjList;
    Vertice(){};
    void addAresta(int destino, int capacidade){
        adjList.insert({destino,Aresta(capacidade)});
    }
}Vertice;


class Grafo {
public:

    Grafo(int vertices, int arestas);
    void out();
    
private:
    //indices dos nós superFonte e superDreno
    int fonte;
    int dreno;
    //vertices do grafo
    std::map<int,Vertice> vertices;
    //função de instanciação do grafo
    void addVertice(int id);
    void addAresta(int id, int destino, int capacidade);
    
    //Funções para a resolução do problema
    bool bfsFordFulkerson(std::map<int, int>& parent);
    void fordFulkerson();
    void encontrarConexoesCriticas();
    int energiaNaoAtendida(); // energiaExigida - energiaAtendida
    int energiaPerdida(); // enrgiaFornecida - energiaAtendida

    //atributos utilitários para a saída.
    std::vector<std::tuple<int, int, int>> conexoesCriticas;
    int energiaAtendida; // fluxo maximo do grafo
    int energiaExigida;
    int energiaFornecida;
};
#endif