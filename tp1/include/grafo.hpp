#ifndef GRAFO_HPP
#define GRAFO_HPP


#include <unordered_map>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <string>
#include <stack>

using namespace std;

class Grafo {
    private:
        vector<string> cidades;
        unordered_map<string, vector<string>> listaAdjacencia;

    public:
        void addCidade(const string& nome);
        void addEstrada(const string& saida, const string& destino);
        bool hasEstrada(const string& saida, const string& destino) const;
        const vector<string>& getAdjacencia(const string& nome) const;
        const vector<string> getCidades() const;

        int* bfsDistanciaMaxima(const string& cidadeInicial) const;

        void dfs(const string& cidadeInicial, unordered_map<string, bool>& visitado, stack<string>& ordem) const;
        Grafo transpor() const;
        void dfs(const string& cidadeInicial, unordered_map<string, bool>& visitado, vector<string>& cfc) const;
        vector<vector<string>> kosaraju();

        bool verificaGrausEntradaSaida() const;
        bool verificaCicloEuleriano() const;


};

#endif
