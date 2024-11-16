#ifndef GRAFO_HPP
#define GRAFO_HPP


#include <unordered_map>
#include <unordered_set>
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
        bool hasCidade(const vector<string>& componente, const string& cidade) const;

        const vector<string>& getAdjacencia(const string& nome) const;
        const vector<string> getCidades() const;

        int* bfsDistanciaMaxima(const string& cidadeInicial) const;
        vector<string> bfs(const string& start, const string& end);

        void dfs(const string& cidadeInicial, unordered_map<string, bool>& visitado, stack<string>& ordem) const;
        Grafo transpor() const;
        void dfs(const string& cidadeInicial, unordered_map<string, bool>& visitado, vector<string>& cfc) const;
        vector<vector<string>> kosaraju();

        void identificarExcessos(const vector<string>& cfc, vector<string>& excessosEntrada, vector<string>& excessosSaida) const;
        void balancearGrafo(vector<string>& excessosEntrada, vector<string>& excessosSaida);
        bool verificaEuleriano(const vector<string>& cfc) const;
        vector<string> hierholzer(const vector<string>& cfc);


};

#endif
