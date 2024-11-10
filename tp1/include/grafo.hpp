    #ifndef GRAFO_HPP
    #define GRAFO_HPP

    #include <unordered_map>
    #include <vector>
    #include <queue>
    #include <string>
    #include <stack>
    #include "cidade.hpp"

    using namespace tsd;

    class Grafo {
    private:
        unordered_map<string, Cidade> cidades;
        unordered_map<string, vector<string>> lista_Adjacencia;

    public:
        void addCidade(const string& nome);
        void addEstrada(const string& saida, const string& destino);
        bool hasEstrada(const string& saida, const string& destino) const;
        const vector<string>& getAdjacencia(const string& nome) const;

        bool verificaCicloEuleriano() const;
        void dfs(const string& cidadeInicial, unordered_map<string, bool>& visitado) const;
        int bfsDistanciaMaxima(const string& cidadeInicial) const;
        Grafo transpor() const;
        vector<vector<string>> encontrarComponentesFortementeConectados();

    };

    #endif
