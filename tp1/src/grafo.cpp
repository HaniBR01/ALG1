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

bool Grafo::hasCidade(const vector<string>& componente, const string& cidade) const{
    for (const auto& centro : componente) {
        if (centro == cidade) {
            return true;
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

    if (listaAdjacencia.find(cidadeInicial) != listaAdjacencia.end()) {
        for (const auto& vizinho : listaAdjacencia.at(cidadeInicial)) {
            if (!visitado[vizinho]) {
                dfs(vizinho, visitado, ordem);
            }
        }
    }

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
    cfc.push_back(cidadeInicial);

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
    stack<string> ordem;
    vector<vector<string>> componentes;

    for (const auto& cidade : cidades) {
        if (!visitado[cidade]) {
            dfs(cidade, visitado, ordem);
        }
    }

    Grafo transposto = this->transpor();

    for (auto& [key, value] : visitado) {
        value = false;
    }

    while (!ordem.empty()) {
        string cidade = ordem.top();
        ordem.pop();

        if (!visitado[cidade]) {
            vector<string> cfc;
            transposto.dfs(cidade, visitado, cfc);
            componentes.push_back(cfc);
        }
    }

    return componentes;
}

void Grafo::identificarExcessos(const vector<string>& cfc,
                                vector<string>& excessosEntrada,
                                vector<string>& excessosSaida) const {
    
    unordered_map<string, int> outDegree, inDegree;
    for (const auto& cidade : cfc) {
        outDegree[cidade] = 0;
        inDegree[cidade] = 0;
    }

    for (const auto& cidade : cfc) {
        for (const auto& vizinho : listaAdjacencia.at(cidade)) {
            if (hasCidade(cfc,vizinho)) {
                outDegree[cidade]++;
                inDegree[vizinho]++;
            }
        }
    }

    for (const auto& cidade : cfc) {
        int saida = outDegree[cidade];
        int entrada = inDegree[cidade];

        if (saida > entrada) {
            excessosSaida.push_back(cidade);
        } else if (entrada > saida) {
            excessosEntrada.push_back(cidade);
        }
    }
}

vector<string> Grafo::bfs(const string& start, const string& end) {
    unordered_map<string, string> parent;
    unordered_set<string> visited;
    queue<string> q;
    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        string cidadeAtual = q.front();
        q.pop();

        if (cidadeAtual == end) {
            vector<string> caminho;
            while (cidadeAtual != start) {
                caminho.push_back(cidadeAtual);
                cidadeAtual = parent[cidadeAtual];
            }
            caminho.push_back(start);

            vector<string> caminhoRevertido;
            for (size_t i = caminho.size() - 1; i != static_cast<size_t>(-1); --i) {
                caminhoRevertido.push_back(caminho[i]);
            }
            return caminhoRevertido;
        }

        for (const string& vizinho : this->getAdjacencia(cidadeAtual)) {
            if (visited.find(vizinho) == visited.end()) {
                visited.insert(vizinho);
                parent[vizinho] = cidadeAtual;
                q.push(vizinho);
            }
        }
    }
    return {};
}

void Grafo::balancearGrafo(vector<string>& excessosEntrada, vector<string>& excessosSaida) {
    for (size_t i = 0; i <= excessosEntrada.size() - 1; i++) {
        auto cidadeEntrada = excessosEntrada[i];
        auto cidadeSaida= excessosSaida[i];
        vector<string> caminho = bfs(cidadeEntrada, cidadeSaida);

        if (!caminho.empty()) {
            for (size_t i = 0; i < caminho.size() - 1; ++i) {
                addEstrada(caminho[i], caminho[i + 1]);
            }
        }
        
    }
}

bool Grafo::verificaEuleriano(const vector<string>& cfc) const {
    unordered_map<string, int> inDegree, outDegree;

    for (const auto& cidade : cfc) {
        outDegree[cidade] = 0;
        for (const auto& vizinho : listaAdjacencia.at(cidade)) {
            if (hasCidade(cfc, vizinho)) {
                outDegree[cidade]++;
                inDegree[vizinho]++;
            }
        }
    }

    for (const auto& cidade : cfc) {
        if (inDegree[cidade] != outDegree[cidade]) {
            return false;
        }
    }
    return true;
}

vector<string> Grafo::hierholzer(const vector<string>& cfc) {
    unordered_map<string, vector<string>> adjCopy = listaAdjacencia;
    stack<string> pilha;
    vector<string> circuito;
    string start = cfc.front();
    string candidato;

    pilha.push(start);
    while (!pilha.empty()) {
        string cidade = pilha.top();
        if (!adjCopy[cidade].empty()) {
            candidato = adjCopy[cidade].back();
            adjCopy[cidade].pop_back();
            if(hasCidade(cfc,candidato)){
                pilha.push(candidato);
            }
        } else {
            circuito.push_back(cidade);
            pilha.pop();
        }
    }
    return circuito;
}
