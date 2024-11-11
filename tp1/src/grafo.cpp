#include "grafo.hpp"

void Grafo::addCidade(const string& nome) {
    for (const auto& c : cidades)
        if (c == nome)
            return;

    cidades.push_back(nome);
}

void Grafo::addEstrada(const string& saida, const string& destino) {
    addCidade(saida);
    addCidade(destino);
    listaAdjacencia[saida].push_back(destino);
}

bool Grafo::hasEstrada(const string& saida, const string& destino) const {
    auto it = listaAdjacencia.find(saida);
    if (it != listaAdjacencia.end()) {
        for (const auto& dest : it->second) {
            if (dest == destino) return true;
        }
    }
    return false;
}

const vector<string>& Grafo::getAdjacencia(const string& nome) const {
    return listaAdjacencia.at(nome);
}

const vector<string> Grafo::getCidades() const {
    return cidades;
}

int* Grafo::bfsDistanciaMaxima(const string& cidadeInicial) const {
    unordered_map<string, int> distancia;
    for (const auto& cidade : cidades) {
        distancia[cidade] = -1;
    }
    distancia[cidadeInicial] = 0;

    queue<string> fila;
    fila.push(cidadeInicial);

    int* distanciaMaxima = new int[2];
    distanciaMaxima[0] = 0;
    distanciaMaxima[1] = 1;
    while (!fila.empty()) {
        string atual = fila.front();
        fila.pop();
        if(listaAdjacencia.find(atual) != listaAdjacencia.end()){
            for (const auto& vizinho : listaAdjacencia.find(atual)->second) {
                if (distancia.find(vizinho)->second == -1) {
                    distancia.find(vizinho)->second = distancia.find(atual)->second + 1;
                    distanciaMaxima[0] = (distanciaMaxima[0] > distancia.find(vizinho)->second) ? distanciaMaxima[0] : distancia.find(vizinho)->second;
                    fila.push(vizinho);
                    distanciaMaxima[1] += 1;
                }
            }
        }
    }
    return distanciaMaxima;
}

void Grafo::dfs(const string& cidadeInicial, unordered_map<string, bool>& visitado, stack<string>& ordem) const {
    visitado[cidadeInicial] = true;
    
    // Se a cidade tem vizinhos, visitamos eles recursivamente
    if (listaAdjacencia.find(cidadeInicial) != listaAdjacencia.end()) {
        for (const auto& vizinho : listaAdjacencia.at(cidadeInicial)) {
            if (!visitado[vizinho]) {
                dfs(vizinho, visitado, ordem);
            }
        }
    }
    
    // Após visitar todos os vizinhos, empurramos a cidade para a pilha
    ordem.push(cidadeInicial);
}

Grafo Grafo::transpor() const {
    Grafo transposto;
    for (const auto& cidade : cidades) {
        transposto.addCidade(cidade);
    }
    for (const auto& [cidade, vizinhos] : listaAdjacencia) {
        for (const auto& vizinho : vizinhos) {
            transposto.addEstrada(vizinho, cidade);
        }
    }
    return transposto;
}

void Grafo::dfs(const string& cidadeInicial, unordered_map<string, bool>& visitado, vector<string>& cfc) const {
    visitado[cidadeInicial] = true;
    cfc.push_back(cidadeInicial);  // Adiciona a cidade à componente fortemente conexa

    if (listaAdjacencia.find(cidadeInicial) != listaAdjacencia.end()) {
        for (const auto& vizinho : listaAdjacencia.at(cidadeInicial)) {
            if (!visitado[vizinho]) {
                dfs(vizinho, visitado, cfc);
            }
        }
    }
}

vector<vector<string>> Grafo::kosaraju() {
    unordered_map<string, bool> visitado;
    stack<string> ordem;  // Pilha para armazenar a ordem de término dos nós
    vector<vector<string>> componentes;

    // Passo 1: DFS no grafo original
    for (const auto& cidade : cidades) {
        if (!visitado[cidade]) {
            dfs(cidade, visitado, ordem);
        }
    }

    // Passo 2: Transpor o grafo
    Grafo transposto = this->transpor();

    // Passo 3: DFS no grafo transposto usando a ordem da pilha
    fill(visitado.begin(), visitado.end(), false);  // Limpar o vetor de visitados para a segunda DFS

    while (!ordem.empty()) {
        string cidade = ordem.top();
        ordem.pop();

        // Se a cidade ainda não foi visitada, ela pertence a uma nova CFC
        if (!visitado[cidade]) {
            vector<string> cfc;
            transposto.dfs(cidade, visitado, cfc);  // Realiza a DFS no grafo transposto
            componentes.push_back(cfc);  // Adiciona a componente fortemente conexa
        }
    }

    return componentes;
}