#include "grafo.hpp"

void Grafo::addCidade(const string& nome) {
    if (cidades.find(nome) == cidades.end()) {
        cidades[nome] = Cidade(nome);
        lista_Adjacencia[nome] = {};
    }
}

void Grafo::addEstrada(const string& saida, const string& destino) {
    addCidade(saida);
    addCidade(destino);
    lista_Adjacencia[saida].push_back(destino);
}

bool Grafo::hasEstrada(const string& saida, const string& destino) const {
    auto it = lista_Adjacencia.find(saida);
    if (it != lista_Adjacencia.end()) {
        for (const auto& dest : it->second) {
            if (dest == destino) return true;
        }
    }
    return false;
}

const vector<string>& Grafo::getAdjacencia(const string& nome) const {
    return lista_Adjacencia.at(nome);
}

void Grafo::dfs(const string& cidadeInicial, unordered_map<string, bool>& visitado) const {
    visitado[cidadeInicial] = true;
    for (const auto& vizinho : lista_Adjacencia.at(cidadeInicial)) {
        if (!visitado[vizinho]) {
            dfs(vizinho, visitado);
        }
    }
}

int Grafo::bfsDistanciaMaxima(const string& cidadeInicial) const {
    unordered_map<string, int> distancia;
    for (const auto& cidade : cidades) {
        distancia[cidade.first] = -1;
    }
    distancia[cidadeInicial] = 0;

    queue<string> fila;
    fila.push(cidadeInicial);

    int distanciaMaxima = 0;
    while (!fila.empty()) {
        string atual = fila.front();
        fila.pop();

        for (const auto& vizinho : lista_Adjacencia.at(atual)) {
            if (distancia[vizinho] == -1) { // Não visitado
                distancia[vizinho] = distancia[atual] + 1;
                if (distancia[vizinho] > distanciaMaxima) {
                    distanciaMaxima = distancia[vizinho];
                }
                fila.push(vizinho);
            }
        }
    }
    return distanciaMaxima;
}

Grafo Grafo::transpor() const {
    Grafo transposto;
    for (const auto& cidade : cidades) {
        transposto.addCidade(cidade.first);
    }
    for (const auto& [cidade, vizinhos] : lista_Adjacencia) {
        for (const auto& vizinho : vizinhos) {
            transposto.addEstrada(vizinho, cidade);
        }
    }
    return transposto;
}

vector<vector<string>> Grafo::encontrarComponentesFortementeConectados() {
    unordered_map<string, bool> visitado;
    stack<string> ordem;
    vector<vector<string>> componentes;

    for (const auto& cidade : cidades) {
        if (!visitado[cidade.first]) {
            dfs(cidade.first, visitado);
            ordem.push(cidade.first);
        }
    }

    visitado.clear();
    Grafo transposto = this->transpor();

    while (!ordem.empty()) {
        string cidade = ordem.top();
        ordem.pop();

        if (!visitado[cidade]) {
            vector<string> componente;
            transposto.dfs(cidade, visitado);
            for (const auto& [nome, foiVisitado] : visitado) {
                if (foiVisitado) componente.push_back(nome);
            }
            componentes.push_back(componente);
        }
    }
    return componentes;
}
