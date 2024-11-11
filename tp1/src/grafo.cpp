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
        distancia.at(cidade.first) = -1;
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
                distanciaMaxima = max(distanciaMaxima, distancia[vizinho]);
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
        if (!visitado.at(cidade.first)) {
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

bool Grafo::verificaCicloEuleriano() const {
    // Verificar se todos os vértices com arestas possuem grau par
    for (const auto& cidade : lista_Adjacencia) {
        if (cidade.second.size() % 2 != 0) {
            return false; // Se algum vértice tem grau ímpar, não pode ser Euleriano
        }
    }

    // Verificar se o grafo é conexo (exceto os vértices com grau 0)
    unordered_map<string, bool> visitado;
    string cidadeInicial;
    bool encontrou = false;
    
    for (const auto& cidade : cidades) {
        if (lista_Adjacencia.at(cidade.first).size() > 0) {
            cidadeInicial = cidade.first;
            encontrou = true;
            break;
        }
    }

    if (!encontrou) {
        return false; // Se não houver arestas, o grafo é trivialmente Euleriano
    }

    dfs(cidadeInicial, visitado);

    // Verificar se todos os vértices com grau maior que 0 foram visitados
    for (const auto& cidade : cidades) {
        if (lista_Adjacencia.at(cidade.first).size() > 0 && !visitado.at(cidade.first)) {
            return false; // Se algum vértice não foi visitado, não é Euleriano
        }
    }

    return true; // Grafo é Euleriano
}

bool Grafo::verificaGrausEntradaSaida() const {
    // Verifica os graus de entrada e saída para todos os vértices
    unordered_map<string, int> grauEntrada;
    unordered_map<string, int> grauSaida;

    // Inicializa os graus
    for (const auto& cidade : cidades) {
        grauEntrada.at(cidade.first) = 0;
        grauSaida.at(cidade.first) = 0;
    }

    // Conta os graus de entrada e saída
    for (const auto& cidade : lista_Adjacencia) {
        for (const auto& vizinho : cidade.second) {
            grauEntrada[vizinho]++;  // A cidade 'vizinho' tem uma aresta de entrada
            grauSaida.at(cidade.first)++;  // A cidade 'cidade.first' tem uma aresta de saída
        }
    }

    // Verifica se todos os vértices têm grau de entrada igual ao grau de saída
    for (const auto& cidade : cidades) {
        if (grauEntrada.at(cidade.first) != grauSaida.at(cidade.first)) {
            return false; // Se algum vértice não tiver grau de entrada igual ao de saída, retorna falso
        }
    }

    return true; // Todos os vértices têm grau de entrada igual ao de saída
}

string Grafo::encontrarCapital() const {
    int distanciaMinima = INT_MAX; // Inicializa com o valor máximo possível
    string cidadeCapital;

    // Para cada cidade, calcular a distância máxima para todas as outras cidades
    for (const auto& cidade : cidades) {
        int distanciaMaxima = bfsDistanciaMaxima(cidade.first); // Calcula a maior distância a partir dessa cidade
        if (distanciaMaxima < distanciaMinima) {
            distanciaMinima = distanciaMaxima;
            cidadeCapital = cidade.first;
        }
    }

    return cidadeCapital; // Retorna a cidade com a menor distância máxima
}
